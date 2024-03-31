#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;

void turnGreen(int* p)
{
    if (*p == 1)
    {
        *p = 2;
    } 
    else
    {
        *p = 1;
    }
}

void carArrived(int car_id, int road_id, int direct, int* p)
{
    std::lock_guard<std::mutex> lg(mtx);
    const char* road;
    if (road_id == 1)
    {
        road = "A";
    }
    else
    {
        road = "B";
    }
    std::cout << "Car " << car_id << " Has Passed Road " << road << " In Direction " << direct << "\n"; 
}

int main()
{
    std::vector<int> cars = {1, 3, 5, 2, 4};
    std::vector<int> directions = {2, 1, 2, 4, 3};
    std::vector<int> arrivalTimes = {10, 20, 30, 40, 50};

    int p = 1;
    for (size_t i = 0; i < cars.size(); ++i)
    {
        if (directions[i] <= 2 && p != 1)
        {
            p = 1;
        }
        else if (directions[i] > 2 && p != 2)
        {
            p = 2;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(arrivalTimes[i]));
        
        carArrived(cars[i], p, directions[i], &p);
        
        if (p == 1 && i + 1 < cars.size() && directions[i + 1] > 2)
        {
            std::cout << "Traffic Light On Road B Is Green\n"; 
        } 
        else if (p == 2 && i + 1 < cars.size() && directions[i + 1] <= 2)
        {
            std::cout << "Traffic Light On Road A Is Green\n";
        }
    }

    return 0;
}
