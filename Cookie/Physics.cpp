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
#include "CircleBody.h"

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
                Cookie::PhysicsBodyType bodyAType = nodeAPtr->physics_body()->body_type();
                Cookie::PhysicsBodyType bodyBType = nodeBPtr->physics_body()->body_type();
                if(bodyAType == RECTANGLE_BODY)
                {
                    if(bodyBType == RECTANGLE_BODY)
                    {
                        resolve_collision(
                                          *(static_cast<Cookie::RectBody*>(nodeAPtr->physics_body())),
                                          *(static_cast<Cookie::RectBody*>(nodeBPtr->physics_body()))
                                          );
                    }else if(bodyAType == CIRCLE_BODY)
                    {
                        resolve_collision(
                                          *(static_cast<Cookie::RectBody*>(nodeAPtr->physics_body())),
                                          *(static_cast<Cookie::CircleBody*>(nodeBPtr->physics_body()))
                                          );
                    }
                }else if (nodeAPtr->physics_body()->body_type() == CIRCLE_BODY)
                {
                    if(bodyAType == CIRCLE_BODY)
                    {
                        resolve_collision(
                                          *(static_cast<Cookie::CircleBody*>(nodeAPtr->physics_body())),
                                          *(static_cast<Cookie::CircleBody*>(nodeBPtr->physics_body()))
                                          );
                    }
                }
            }
        }
    }
}

void Cookie::Physics::resolve_collision(Cookie::RectBody& bodyA, Cookie::RectBody& bodyB)
{
    Cookie::Rect rectA = bodyA.rectangle().centered_rect() + bodyA.node()->position_world();
    Cookie::Rect rectB = bodyB.rectangle().centered_rect() + bodyB.node()->position_world();
    
    if(rectA.intersects(rectB))
    {
        Cookie::Vector p;
        if(bodyA.velocity().length_squared() >
           bodyB.velocity().length_squared())
        {
            p = rectA.penetration(rectB);
            bodyA.node()->translate_by(p.x, p.y);
        }else{
            p = rectB.penetration(rectA);
            bodyB.node()->translate_by(p.x, p.y);
        }
        
        const Cookie::Float massA = bodyA.mass();
        const Cookie::Float massB = bodyB.mass();
        const Cookie::Vector velA = bodyA.velocity();
        const Cookie::Vector velB = bodyB.velocity();
        
        // Resolve Collision
        if(p.x == 0) //Collision is along the X axis
        {
            if(bodyA.dynamic())
            {
                Cookie::Vector newVelA = velA;
                newVelA.y = (bodyA.restitution()*newVelA.y*(massA-massB) + 2*massB*velB.y)
                / (massA+massB);
                if(fabsf(newVelA.y) < 5) newVelA.y = 0;
                bodyA.set_velocity(newVelA);
            }
            if(bodyB.dynamic())
            {
                Cookie::Vector newVelB = velB;
                newVelB.y = (newVelB.y*(massB-massA) + 2*massA*velA.y) / (massB+massA);
                if(fabsf(newVelB.y) < 5) newVelB.y = 0;
                bodyB.set_velocity(newVelB);
            }
        }else{ //Collision is along the Y axis
            if(bodyA.dynamic())
            {
                Cookie::Vector newVelA = velA;
                newVelA.x = (bodyA.restitution()*newVelA.x*(massA-massB) + 2*massB*velB.x)
                / (massA+massB);
                bodyA.set_velocity(newVelA);
            }
            if(bodyB.dynamic())
            {
                Cookie::Vector newVelB = velB;
                newVelB.x = (newVelB.x*(massB-massA) + 2*massA*velA.x) / (massB+massA);
                bodyB.set_velocity(newVelB);
            }
        }
    }
}

void Cookie::Physics::resolve_collision(Cookie::RectBody& bodyA, Cookie::CircleBody& bodyB)
{
}

void Cookie::Physics::resolve_collision(Cookie::CircleBody& bodyA, Cookie::CircleBody& bodyB)
{
}
