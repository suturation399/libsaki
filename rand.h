#ifndef SAKI_RAND_H
#define SAKI_RAND_H

#include <random>
#include <cstdint>



namespace saki
{



class Rand
{
public:
    Rand();
    Rand(const Rand &copy) = default;
    Rand &operator=(const Rand &assign) = default;
    ~Rand() = default;

    int32_t gen();
    int32_t gen(int32_t mod);
    uint32_t state() const;
    void set(uint32_t state);

private:
    std::minstd_rand mGen;
    std::uniform_int_distribution<int> mDist;
};



} // namespace saki



#endif // SAKI_RAND_H


