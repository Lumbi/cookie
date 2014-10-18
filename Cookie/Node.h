//
//  Node.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Node__
#define __Cookie__Node__

#include <stdio.h>
#include <string>
#include <vector>
#include "Point.h"
#include "Int.h"
#include "Float.h"
#include "Bool.h"
#include "Block.h"
#include "PhysicsBody.h"
#include "Vector.h"

namespace Cookie
{
    class Node
    {
    public:
        Node();
        virtual ~Node();
        
        std::string name() const;
        void set_name(std::string);
        
        Cookie::Point position() const;
        Cookie::Point position_world() const;
        void translate_to(Cookie::Float x, Cookie::Float y);
        void translate_by(Cookie::Float dx, Cookie::Float dy);
        
        Cookie::Float rotation() const;
        void rotate_to(Cookie::Float degrees);
        void rotate_by(Cookie::Float degrees);
        
        Cookie::Float depth() const;
        void set_depth(Cookie::Float);
        
        const std::vector<Node*>& children() const;
        void add_child(Cookie::Node* const child);
        void remove_child(Cookie::Node* const child);
        void remove_all_children();
        std::vector<Cookie::Node*>::iterator children_begin();
        std::vector<Cookie::Node*>::iterator children_end();
        Cookie::Node* const parent() const;
        
        const std::vector<Cookie::Block*>& blocks() const;
        void add_block(Cookie::Block* const block);
        void remove_block(Cookie::Block* const block);
        void remove_all_blocks();
        std::vector<Cookie::Block*>::iterator blocks_begin();
        std::vector<Cookie::Block*>::iterator blocks_end();
        
        Cookie::PhysicsBody* const physics_body() const;
        void set_physics_body(Cookie::PhysicsBody*);

    protected:
        std::string name_;
        Cookie::Node* parent_;
        Cookie::Point position_;
        Cookie::Float rotation_;
        Cookie::Float depth_;
        Cookie::PhysicsBody* physics_body_;

        std::vector<Cookie::Node*> children_;
        std::vector<Cookie::Block*> blocks_;
    };
    
    bool operator==(const Cookie::Node& lhs, const Cookie::Node& rhs);
}

#endif /* defined(__Cookie__Node__) */
