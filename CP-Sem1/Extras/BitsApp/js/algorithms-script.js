var instruction_idx = 0;
var speed = 1000;

function isValid(element, min, max, value) {
    if(isNaN(value)) {
        element.textContent = "Enter a number omg";
        return 0;
    }
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

function getInputNumber() {
    return parseInt(document.getElementById("numberInput").value);
}

function setAnimationSpeed() {
    console.log(5050 - document.getElementById("animationSpeed").value);
    speed = 5050 - document.getElementById("animationSpeed").value;
}

function resetResult() {
    putBits("resultbit", 0);
    document.getElementById("operation").textContent = " ";
}

function setResult(s, mask, operation) {
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
        case '>>':
            result = s >> mask;
            break;
        case '<<':
            result = s << mask;
            break;
    }

    putBits("resultbit", result);
}

function setInstruction(idx, instruction, num_tabs) {
    element = document.getElementById("instruction" + idx);
    element.textContent = instruction;
    element.style.paddingLeft = (num_tabs + 1) * 30  + "px";

}

function putBits(class_name, number) {
    for (var i = 0; i < 16; i++) {
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

function highlightInstruction(idx) {
    document.getElementById("instruction" + instruction_idx).classList.remove("highlight");
    instruction_idx = idx;
    document.getElementById("instruction" + instruction_idx).classList.add("highlight");
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function setVariable(idx, text) {
    element = document.getElementById("variable" + idx);
    element.textContent = text;
}

function resetValues() {
    for(var i = 0; i < 18; ++i) {
        setInstruction(i, "");
    }
    for(var i = 0; i < 5; ++i) {

    }
    result = 0;
    putBits("resultbit", result);
    document.getElementById("operation").textContent = " ";
}

function setNaiveCountCode() {
    setInstruction(0, "int count = 0;", 0);
    setInstruction(1, "for(int i = 0; i < sizeof(s) * 8; ++i) {", 0);
    setInstruction(2, "if((s & (1 << i)) != 0) {", 1);
    setInstruction(3, "++count;", 2);
    setInstruction(4, "}", 1);
    setInstruction(5, "}", 0);
}

function setNaiveCountVariables(s, count, i) {
    setVariable(0, "s = " + s);
    setVariable(1, "count = " + count);
    setVariable(2, "i = " + i);
}

async function naiveCount() {
    var number = getInputNumber();

    if(isValid(document.getElementById("numberError"), 0, 65535, number)) {
        resetValues();
        setNaiveCountCode();
        setVariable(0, "s = " + number);
        resetResult();

        putBits("sbit", number);

        var count = 0;
        highlightInstruction(0);
        setVariable(1, "count = " + count);
        await sleep(speed);

        for(var i = 0; i < 16; ++i) {
            resetResult();
            putBits("maskbit", 0);
            setNaiveCountVariables(number, count, i);
            highlightInstruction(1);
            await sleep(speed);

            putBits("maskbit", 1);
            highlightInstruction(2);
            await sleep(speed);

            putBits("maskbit", (1 << i));
            await sleep(speed);

            setResult(number, (1 << i), "&")
            await sleep(speed);
            if((number & (1 << i)) != 0) {
                ++count;
                highlightInstruction(3);
                await sleep(speed);
            }
            setNaiveCountVariables(number, count, i);
        }
        highlightInstruction(5);
        putBits("maskbit", 0);
    }
}

function setExtractNibblesCode() {
    setInstruction(0, "for(int i = 0; i < sizeof(s) * 2; ++i) {", 0);
    setInstruction(1, "int nibble = (s & (0xF << (i * 4)));", 1);
    setInstruction(2, "}", 0);
}

async function extractNibbles() {
    var number = getInputNumber();

    if(isValid(document.getElementById("numberError"), 0, 65535, number)) {
        resetValues();
        setExtractNibblesCode();
        setVariable(0, "s = " + number);
        resetResult();

        putBits("sbit", number);

        for(var i = 0; i < 4; ++i) {
            resetResult();
            putBits("maskbit", 0);
            setVariable(1, "i = " + i);
            setVariable(2, "");
            highlightInstruction(0);
            await sleep(speed);

            var nibble = (number & (0xF << (i * 4)));
            putBits("maskbit", 0xF);
            highlightInstruction(1);
            if(i != 0) {
                await sleep(speed);

                putBits("maskbit", (0xF << (i * 4)));
                await sleep(speed);
            }

            setResult(number, (0xF << (i * 4)), "&");
            setVariable(2, "nibble = " + (number & (0xF << (i * 4))));
            await sleep(speed);
        }
        highlightInstruction(2);
    }
}

function setReverseNibblesCode() {
    setInstruction(0, "for(int i = 0; i < sizeof(s) * 2; ++i) {", 0);
    setInstruction(1,"int nibble_pos = i * 4;", 1);
    setInstruction(2,"int nibble = s & (0xF << nibble_pos);", 1);
    setInstruction(3,"nibble = nibble >> nibble_pos;", 1);
    setInstruction(4, "// Reverse bits", 1);
    setInstruction(5,"int bit0 = nibble & (1 << 0);", 1);
    setInstruction(6,"int bit1 = nibble & (1 << 1);", 1);
    setInstruction(7,"int bit2 = nibble & (1 << 2);", 1);
    setInstruction(8,"int bit3 = nibble & (1 << 3);", 1);
    setInstruction(9,"nibble = (bit0 << 3) | (bit1 << 1)", 1);
    setInstruction(10," | (bit2 >> 1) | (bit3 >> 3);", 3);
    setInstruction(11,"// Reset and put bits", 1);
    setInstruction(12,"s = s & ~(0xF << nibble_pos);", 1);
    setInstruction(13,"s = s | (nibble << nibble_pos);", 1);
    setInstruction(14,"}", 0);
}

async function reverseNibbles() {
    var number = getInputNumber();

    if(isValid(document.getElementById("numberError"), 0, 65535, number)) {
        resetValues();
        setReverseNibblesCode();
        setVariable(0, "s = " + number);
        resetResult();

        for(var i = 0; i < 4; ++i) {
            resetResult();
            document.getElementById("number").textContent = "S";
            putBits("sbit", number);
            putBits("maskbit", 0);
            for(var x = 2; x < 8; ++x) {
                setVariable(x, "");
            }

            setVariable(1, "i = " + i);
            highlightInstruction(0);
            await sleep(speed);

            var nibble_position = i * 4;
            setVariable(2, "nibble_pos = " + i * 4);
            highlightInstruction(1);
            await sleep(speed);

            var nibble = number & (0xF << nibble_position);
            putBits("maskbit", 0xF);
            highlightInstruction(2);
            if(nibble_position != 0) {
                await sleep(speed);

                putBits("maskbit", (0xF << nibble_position));
                await sleep(speed);
            }

            setResult(number, (0xF << nibble_position), "&");
            setVariable(3, "nibble = " + nibble);
            await sleep(speed);

            nibble = nibble >> nibble_position;
            highlightInstruction(3);
            setResult(nibble << nibble_position, nibble_position, ">>");
            setVariable(3, "nibble = " + nibble);
            await sleep(speed);
            
            var bit0 = nibble & (1 << 0);
            highlightInstruction(5);
            document.getElementById("number").textContent = "N";
            putBits("sbit", nibble);
            putBits("maskbit", 1);
            setResult(nibble, 1, "&");
            setVariable(4, "bit0 = " + bit0);
            await sleep(speed);

            var bit1 = nibble & (1 << 1);
            highlightInstruction(6);
            putBits("sbit", nibble);
            putBits("maskbit", 2);
            setResult(nibble, 2, "&");
            setVariable(5, "bit1 = " + bit1);
            await sleep(speed);

            var bit2 = nibble & (1 << 2);
            highlightInstruction(7);
            putBits("sbit", nibble);
            putBits("maskbit", 4);
            setResult(nibble, 4, "&");
            setVariable(6, "bit2 = " + bit2);
            await sleep(speed);

            var bit3 = nibble & (1 << 3);
            highlightInstruction(8);
            putBits("sbit", nibble);
            putBits("maskbit", 8);
            setResult(nibble, 8, "&");
            setVariable(7, "bit3 = " + bit3);
            await sleep(speed);
            
            nibble = (bit0<<3) | (bit1<<1) | (bit2>>1) | (bit3>>3);
            highlightInstruction(9);
            document.getElementById("number").textContent = "0";
            document.getElementById("mask").textContent = "1";
            putBits("sbit", bit0 << 3);
            putBits("maskbit", bit1 << 1);
            setResult(bit0 << 3, bit1 << 1, "|");
            await sleep(speed);

            highlightInstruction(10);
            document.getElementById("number").textContent = "B";
            document.getElementById("mask").textContent = "2";
            putBits("sbit", (bit0<<3) | (bit1<<1));
            putBits("maskbit", bit2 >> 1);
            setResult((bit0<<3) | (bit1<<1), bit2 >> 1, "|");
            await sleep(speed);
            
            document.getElementById("mask").textContent = "3";
            putBits("sbit", (bit0<<3) | (bit1<<1) | (bit2>>1));
            putBits("maskbit", bit3 >> 3);
            setResult((bit0<<3) | (bit1<<1) | (bit2>>1), bit3 >> 3, "|");
            await sleep(speed);
            
            document.getElementById("number").textContent = "S";
            document.getElementById("mask").textContent = "M";

            highlightInstruction(12);
            putBits("sbit", number);
            putBits("maskbit", 0xF);
            await sleep(speed);

            putBits("maskbit", (0xF << nibble_position));
            await sleep(speed);

            putBits("maskbit", (~(0xF << nibble_position)) & 0xFFFF);
            await sleep(speed);

            setResult(number, (~(0xF << nibble_position)) & 0xFFFF, "&");
            setVariable(0, "s = " + number);
            await sleep(speed);
            number = number & ~(0xF << nibble_position);

            highlightInstruction(13);
            putBits("sbit", number);
            putBits("maskbit", nibble);
            await sleep(speed);

            putBits("maskbit", nibble << nibble_position);
            await sleep(speed);

            setResult(number, (nibble << nibble_position), "|");
            setVariable(0, "s = " + number);
            await sleep(speed);
            number = number | (nibble << nibble_position);
        }
        highlightInstruction(14);
    }
}

function setKernighanCode() {
    setInstruction(0, "int count = 0;", 0);
    setInstruction(1, "while(s) {", 0);
    setInstruction(2, "s = s & (s - 1);", 1);
    setInstruction(3, "++count", 1);
    setInstruction(4, "}", 0);
}

async function kernighan() {
    var number = getInputNumber();

    if(isValid(document.getElementById("numberError"), 0, 65535, number)) {
        resetValues();
        setKernighanCode();
        setVariable(0, "s = " + number);
        resetResult();

        var count = 0;
        highlightInstruction(0);
        setVariable(1, "count = " + count);
        await sleep(speed);

        while(number) {
            putBits("sbit", 0);
            putBits("maskbit", 0);
            resetResult();
            highlightInstruction(1);
            await sleep(speed);

            highlightInstruction(2);
            putBits("sbit", number);
            putBits("maskbit", number);
            await sleep(speed);

            putBits("maskbit", number - 1);
            await sleep(speed);

            setResult(number, number - 1, "&");
            await sleep(speed);
            number = number & (number - 1);

            ++count;
            highlightInstruction(3);
            setVariable(1, "count = " + count);
            await sleep(speed);
        }
        highlightInstruction(4);
    }
}