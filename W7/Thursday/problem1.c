/*
    Rotate the nibbles of a given unsigned number by moving the middle two hex symbols to the edges. 
    For example,
        0x12344321 becomes 0x41233214 after rotation
        0x12345678 becomes 0x41236785. 
        
        The unsigned number is represented in 8 hex symbols, and each nibble is 1 hex symbol.

    Solve plan: 
        1. Extract the two middle nibbles.
            0x12344321 -> Nib1 = 4 Nib2 = 4
            0x12345678 -> Nib1 = 4 Nib2 = 5
        2. Shift the halves of the number towards the middle by one nibble.
            0x12344321 -> 0x01233210
            0x12345678 -> 0x01236780
        3. Set the end nibbles with Nib1 and Nib2
            0x01233210 -> 0x41233214
            0x01236780 -> 0x41236785

    Questions ?
*/

// Run 'make test_get_nibble' after implementation
unsigned get_nibble(unsigned number, unsigned nibblePosition);
// Run 'make test_rotate_halves' after implementation
unsigned rotate_halves(unsigned number);
// Run 'make test_set_nibble' after implementation
unsigned set_nibble_at_position(unsigned number, unsigned nibble, unsigned nibblePosition);

/* unsigned rotate_middle_nibbles(unsigned number) {
    unsigned centralNibbleLeft = get_nibble(number, 4);
    unsigned centralNibbleRight = get_nibble(number, 3);

    number = rotate_halves(number);

    number = set_nibble_at_position(number, centralNibbleLeft, 7);
    number = set_nibble_at_position(number, centralNibbleRight, 0);

    return number;
}*/