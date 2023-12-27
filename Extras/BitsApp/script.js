var s = 0;
var mask = 0;
var operation = null;
var instruction_idx = 0;

function getAnimationSpeed() {
    return document.getElementById("animationSpeed").value;
}

function setInstruction(idx, instruction) {
    document.getElementById("fullCommand").classList.remove("highlight");
    document.getElementById("instruction" + instruction_idx).classList.remove("highlight");
    document.getElementById("instruction" + idx).textContent = instruction;
    instruction_idx = idx;
    document.getElementById("instruction" + instruction_idx).classList.add("highlight");
}

function setFullCommand(command) {
    document.getElementById("instruction" + instruction_idx).classList.remove("highlight");
    document.getElementById("fullCommand").textContent = command;
    document.getElementById("fullCommand").classList.add("highlight");
}

function resetValues() {
    for(var i = 0; i < 4; ++i) {
        setInstruction(i, "");
    }
    setFullCommand("");   
    result = 0;
    putBits("resultbit", result);
    document.getElementById("operation").textContent = " ";
}

function isValid(element, min, max, value) {
    if (value < min) {
        element.textContent = "Number should be >= " + min;
        return 0;
    } else if (value > max) {
        element.textContent = "Number should be <= " + max;
        return 0;
    } else {
        element.textContent = "";
        return 1;
    }
}

function putBits(class_name, number) {
    for (var i = 0; i < 8; i++) {
        var bit = number & 1;
        number = number >> 1;

        element = document.getElementById(class_name + i)
        element.textContent = bit;

        // Add color class if 1
        if (bit === 1) {
            element.classList.add("setBit");
        }
        else {
            element.classList.remove("setBit");
        }
    }
}

function setResult() {
    if (operation != null) {
        document.getElementById("operation").textContent = operation;

        switch (operation) {
            case '|':
                result = s | mask;
                break;
            case '&':
                result = s & mask;
                break;
            case '^':
                result = s ^ mask;
                break;
        }

        putBits("resultbit", result);
    }
}

function setS() {
    var number = parseInt(document.getElementById('setNumber').value);

    if (isValid(document.getElementById("errorSetS"), 0, 255, number)) {
        s = number;
        putBits("sbit", s);

        // Update result if available
        setResult();
    }
}

function setBit() {
    var position = parseInt(document.getElementById('setBitPosition').value);

    if (isValid(document.getElementById("errorSetBit"), 0, 7, position)) {
        resetValues();
        
        var animationSpeed = getAnimationSpeed();

        // Put 1 on position 0
        setTimeout(() => {
            setInstruction(0, "mask = 1;");
            putBits("maskbit", 1);
        }, 0);

        // Shift it to the right position
        setTimeout(() => {
            setInstruction(1, "mask = (mask << " + position + ");");
            mask = (1 << position);
            putBits("maskbit", mask);
        }, animationSpeed);

        setTimeout(() => {
            setInstruction(2, "result = s | mask;");
            operation = '|';
            setResult();
        }, animationSpeed * 2);

        setTimeout(() => {
            setFullCommand("result = s | (1 << " + position + ");");
        }, animationSpeed * 3);
    }
}

function resetBit() {
    var position = parseInt(document.getElementById('resetBitPosition').value);

    if (isValid(document.getElementById("errorResetBit"), 0, 7, position)) {
        resetValues();

        var animationSpeed = getAnimationSpeed();

        // Put 1 on position 0
        setTimeout(() => {
            setInstruction(0, "mask = 1;");
            putBits("maskbit", 1);
        }, 0);

        // Shift it to the right position
        setTimeout(() => {
            setInstruction(1, "mask = (mask << " + position + ");");
            mask = (1 << position);
            putBits("maskbit", mask);
        }, animationSpeed);

        // Apply not
        setTimeout(() => {
            setInstruction(2, "mask = ~mask;");
            mask = 255 - mask;
            putBits("maskbit", mask);
        }, animationSpeed * 2);

        setTimeout(() => {
            setInstruction(3, "result = s & mask;");
            operation = '&';
            setResult();
        }, animationSpeed * 3);

        setTimeout(() => {
            setFullCommand("result = s & ~(1 << " + position + ");");
        }, animationSpeed * 4);
    }
}

function toggleBit() {
    var position = parseInt(document.getElementById('toggleBitPosition').value);

    if (isValid(document.getElementById("errorToggleBit"), 0, 7, position)) {
        resetValues();

        var animationSpeed = getAnimationSpeed();

        // Put 1 on position 0
        setTimeout(() => {
            setInstruction(0, "mask = 1;");
            putBits("maskbit", 1);
        }, 0);

        // Shift it to the right position
        setTimeout(() => {
            setInstruction(1, "mask = (mask << " + position + ");");
            mask = (1 << position);
            putBits("maskbit", mask);
        }, animationSpeed);

        setTimeout(() => {
        setInstruction(2, "result = s ^ mask;");
        operation = '^';
        setResult();
        }, animationSpeed * 2);

        setTimeout(() => {
            setFullCommand("result = s ^ (1 << " + position + ");");
        }, animationSpeed * 3);
    }
}

function getBit() {
    var position = parseInt(document.getElementById('getBitPosition').value);

    if (isValid(document.getElementById("errorGetBit"), 0, 7, position)) {
        resetValues();

        var animationSpeed = getAnimationSpeed();

        // Put 1 on position 0
        setTimeout(() => {
            setInstruction(0, "mask = 1;");
            putBits("maskbit", 1);
        }, 0);

        // Shift it to the right position
        setTimeout(() => {
            setInstruction(1, "mask = (mask << " + position + ");");
            mask = (1 << position);
            putBits("maskbit", mask);
        }, animationSpeed);

        setTimeout(() => {
            setInstruction(2, "result = s & mask;");
            operation = '&';
            setResult();
        }, animationSpeed * 2);

        setTimeout(() => {
            setInstruction(3, "result != 0 ? (BIT IS 1) : (BIT IS 0);");
        }, animationSpeed * 3);

        setTimeout(() => {
            setFullCommand("bool isBitSet = (s & (1 << " + position + ")) != 0;");
        }, animationSpeed * 3);

    }
}