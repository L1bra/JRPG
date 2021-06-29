#ifndef BITMASK_H_
#define BITMASK_H_

#include <stdint.h>

class Bitmask
{
public:
    Bitmask();

    void set_mask(Bitmask& other);
    uint32_t get_mask() const;

    bool get_bit(int pos) const;
    void set_bit(int pos, bool on);
    void set_bit(int pos);
    void clear_bit(int pos);

    void clear();
private:
    uint32_t bits;
};


#endif  // BITMASK_H_