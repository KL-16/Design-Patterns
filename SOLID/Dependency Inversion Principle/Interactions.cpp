#include <iostream>

class InteractiveObject
{
public:
    virtual void interact() = 0;
    virtual ~InteractiveObject() = default;
};

class Door : public InteractiveObject
{
public:
    Door() {}
    void interact() override
    {
        // Open or close the door
        m_open = !m_open;
        if (m_open)
        {
            std::cout << "Door is open" << std::endl;
        }
        else
        {
            std::cout << "Door is closed" << std::endl;
        }
    }

private:
    bool m_open = false;
};

class Ball : public InteractiveObject
{
public:
    Ball() {}
    void interact() override
    {
        // Kick the ball
        std::cout << "Ball is kicked" << std::endl;
    }
};

class Player
{
public:
    Player() {}

    void interactWith(InteractiveObject* obj)
    {
        if (obj)
        {
            obj->interact();
        }
    }
};

int main() {
    Door* door = new Door();
    Player player;
    player.interactWith(door);
    Ball* ball = new Ball();
    player.interactWith(ball);
	return 0;
}