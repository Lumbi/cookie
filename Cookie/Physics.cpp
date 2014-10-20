//
//  Physics.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-16.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Physics.h"
#include "Game.h"
#include <cmath>
#include "RectBody.h"

#pragma mark - Forward Declaration

void get_all_nodes_with_physics_body(std::vector<Cookie::Node*>& vector, Cookie::Node* node);

#pragma mark - Accessors & Mutators

const Cookie::Vector& Cookie::Physics::gravity() const
{
    return gravity_;
}

void Cookie::Physics::set_gravity(Cookie::Vector gravity)
{
    gravity_ = gravity;
}

void get_all_nodes_with_physics_body(std::vector<Cookie::Node*>& vector, Cookie::Node* node)
{
    if(node->physics_body() != NULL)
    {
        vector.push_back(node);
    }
    
    for(auto child = node->children_begin(); child != node->children_end(); ++child)
    {
        get_all_nodes_with_physics_body(vector, *child);
    }
}

#pragma mark - Simulation

void Cookie::Physics::update(Cookie::Game& game)
{
    //Temporary
    static Cookie::Float friction = 0.9f;
    
    std::vector<Cookie::Node*> nodes;
    get_all_nodes_with_physics_body(nodes, game.world());
    
    Cookie::Float time = game.time_elapsed() / 1000.0f;
    
    for(auto node = nodes.begin(); node != nodes.end(); ++node)
    {
        Cookie::Node* nodePtr = *node;
        Cookie::Vector vel = nodePtr->physics_body()->velocity();
        
        if(nodePtr->physics_body()->dynamic())
        {
            if(!nodePtr->physics_body()->ignores_gravity())
            {
                vel += gravity_;
            }
            
            nodePtr->translate_by(vel.x * time, vel.y * time);
            
            //        vel *= friction;
            
            nodePtr->physics_body()->set_velocity(vel);
        }
    }
    
    for(auto nodeA = nodes.begin(); nodeA != nodes.end(); ++nodeA)
    {
        for(auto nodeB = nodes.begin(); nodeB != nodes.end(); ++nodeB)
        {
            Cookie::Node* nodeAPtr = *nodeA;
            Cookie::Node* nodeBPtr = *nodeB;

            if(nodeAPtr != nodeBPtr)
            {
                //check collision
                if(nodeAPtr->physics_body()->body_type() == RECTANGLE_BODY &&
                   nodeBPtr->physics_body()->body_type() == RECTANGLE_BODY)
                {
                    RectBody* nodeABody = static_cast<RectBody*>(nodeAPtr->physics_body());
                    RectBody* nodeBBody = static_cast<RectBody*>(nodeBPtr->physics_body());
                    
                    Cookie::Rect rectA = nodeABody->rectangle().centered_rect() + nodeAPtr->position_world();
                    Cookie::Rect rectB = nodeBBody->rectangle().centered_rect() + nodeBPtr->position_world();
                    
                    if(rectA.intersects(rectB))
                    {
                        Cookie::Vector p;
                        if(nodeABody->velocity().length_squared() >
                           nodeBBody->velocity().length_squared())
                        {
                            p = rectA.penetration(rectB);
                            (*nodeA)->translate_by(p.x, p.y);
                        }else{
                            p = rectB.penetration(rectA);
                            (*nodeB)->translate_by(p.x, p.y);
                        }
                        
                        const Cookie::Float massA = nodeABody->mass();
                        const Cookie::Float massB = nodeBBody->mass();
                        const Cookie::Vector velA = nodeABody->velocity();
                        const Cookie::Vector velB = nodeBBody->velocity();
                        
                        // Resolve Collision
                        if(p.x == 0) //Collision is along the X axis
                        {
                            if(nodeABody->dynamic())
                            {
                                Cookie::Vector newVelA = velA;
                                newVelA.y = (nodeABody->restitution()*newVelA.y*(massA-massB) + 2*massB*velB.y)
                                / (massA+massB);
                                if(fabsf(newVelA.y) < 5) newVelA.y = 0;
                                nodeABody->set_velocity(newVelA);
                            }
                            if(nodeBBody->dynamic())
                            {
                                Cookie::Vector newVelB = velB;
                                newVelB.y = (newVelB.y*(massB-massA) + 2*massA*velA.y) / (massB+massA);
                                if(fabsf(newVelB.y) < 5) newVelB.y = 0;
                                nodeBBody->set_velocity(newVelB);
                            }
                        }else{ //Collision is along the Y axis
                            if(nodeABody->dynamic())
                            {
                                Cookie::Vector newVelA = velA;
                                newVelA.x = (nodeABody->restitution()*newVelA.x*(massA-massB) + 2*massB*velB.x)
                                / (massA+massB);
                                nodeABody->set_velocity(newVelA);
                            }
                            if(nodeBBody->dynamic())
                            {
                                Cookie::Vector newVelB = velB;
                                newVelB.x = (newVelB.x*(massB-massA) + 2*massA*velA.x) / (massB+massA);
                                nodeBBody->set_velocity(newVelB);
                            }
                        }
                    }
                }
            }
        }
    }
}
