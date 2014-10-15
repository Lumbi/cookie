//
//  Node.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include <algorithm>

#include "Node.h"
#include "Point.h"
#include "Rotation.h"
#include "Block.h"

Cookie::Node::Node()
{
    position_ = {0,0};
    rotation_ = 0;
    parent_ = NULL;
    depth_ = 0;
}

#pragma mark - Position

Cookie::Point Cookie::Node::position() const
{
    return position_;
}

Cookie::Point Cookie::Node::position_world() const
{
    Cookie::Point pos_world = position_;
    if(parent_ != NULL)
    {
        pos_world = parent_->position_world();
        pos_world = pos_world + position_.rotate_by(parent_->rotation_);
    }
    return pos_world;
}

void Cookie::Node::translate_by(Cookie::Float dx, Cookie::Float dy)
{
    position_ += {dx, dy};
}

void Cookie::Node::translate_to(Cookie::Float x, Cookie::Float y)
{
    position_ = {x, y};
}

#pragma mark - Depth

Cookie::Float Cookie::Node::depth() const
{
    return depth_;
}

void Cookie::Node::set_depth(Cookie::Float depth)
{
    depth_ = depth;
}

#pragma mark - Rotation

Cookie::Float Cookie::Node::rotation() const
{
    return rotation_;
}

void Cookie::Node::rotate_by(Cookie::Float degrees)
{
    rotation_ = Cookie::wrap_degrees(rotation_+degrees);
}

void Cookie::Node::rotate_to(Cookie::Float degrees)
{
    rotation_ = Cookie::wrap_degrees(degrees);
}

#pragma mark - Hierarchy

const std::vector<Cookie::Node*>& Cookie::Node::children() const{
    return children_;
}

void Cookie::Node::add_child(Cookie::Node* const child)
{
    children_.push_back(child);
}

void Cookie::Node::remove_child(Cookie::Node* const child)
{
    std::vector<Cookie::Node*>::iterator del_pos = std::find(children_.begin(), children_.end(), child);
    if (del_pos != children_.end())
    {
        children_.erase(del_pos);
    }
}

void Cookie::Node::remove_all_children()
{
    children_.clear();
}

std::vector<Cookie::Node*>::iterator Cookie::Node::children_begin()
{
    return children_.begin();
}

std::vector<Cookie::Node*>::iterator Cookie::Node::children_end()
{
    return children_.end();
}

Cookie::Node* const Cookie::Node::parent() const
{
    return parent_;
}

#pragma mark - Blocks

const std::vector<Cookie::Block*>& Cookie::Node::blocks() const
{
    return blocks_;
}

void Cookie::Node::add_block(Cookie::Block* const block)
{
    blocks_.push_back(block);
}

void Cookie::Node::remove_block(Cookie::Block* const block)
{
    blocks_.erase(std::find(blocks_.begin(), blocks_.end(), block), blocks_.end());
}

void Cookie::Node::remove_all_blocks()
{
    blocks_.clear();
}

std::vector<Cookie::Block*>::iterator Cookie::Node::blocks_begin()
{
    return blocks_.begin();
}

std::vector<Cookie::Block*>::iterator Cookie::Node::blocks_end()
{
    return blocks_.end();
}

#pragma mark - Operator Overloading

bool Cookie::operator==(const Cookie::Node& lhs, const Cookie::Node& rhs)
{
    return &lhs == &rhs;
};

