#ifndef CONNECTION_H
#define CONNECTION_H

#pragma once

class Connection
{
public:
    Connection(float weight, bool active = true);
    ~Connection();

    
private:
    float weight{};
    bool active{};
};

#endif