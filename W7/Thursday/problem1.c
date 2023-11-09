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