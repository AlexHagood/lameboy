import json

with open('Opcodes.json', 'r') as file:
    data = json.load(file)



ops = data["unprefixed"];
opsCB = data["cbprefixed"];

regs = ["A", "B", "C", "D", "E", "H", "L", "AF", "BC", "DE", "HL", "SP", "NZ", "NC", "Z"];
regs16 = ["AF", "BC", "DE", "HL", "SP"]

i = 0;


## Disgusting python script. This is just to do the majority of the work, but not all of it. It's out put will need some polishing certainly.
## My only questions is WHY DOES C MEAN BOTH CARRY FLAG AND C REGISTER?!?!? 

for op in opsCB.values():
    mnemonic = op["mnemonic"];
    cycles = op["cycles"][0];
    isize = 0;
    operands = op["operands"];
    if (not operands):
        reg1 = "0"
        reg2 = "0"
    elif (len(operands) > 1): # Two arguments
        if (operands[0]["name"] in regs):
            reg1 = operands[0]["name"]
            if (reg1 in regs16):
                isize |= 0b1
            reg1 = "Regs->" + reg1;
        elif (operands[0]["name"].isdigit()):
            reg1 = 0
        else:
            reg1 = "Regs->SP"
            if (operands[0]["bytes"] == 2):
                isize |= 0b1
        

        if (operands[1]["name"] in regs):
            reg2 = operands[1]["name"]
            if (reg2 in regs16):
                isize |= 0b10
            reg2 = "Regs->" + reg2;
        else:
            reg2 = "Regs->SP"
            if (operands[1]["bytes"] == 2):
                isize |= 0b10

    else: #one arguments
        reg2 = "0"
        if (operands[0]["name"] in regs):
            reg1 = operands[0]["name"]
            if (reg1 in regs16):
                isize |= 0b1
            reg1 = "Regs->" + reg1
        elif (operands[0]["name"][0] == '$'):
            reg1 = "Regs->SP"
        else:
            reg1 = "Regs->SP"
            if (operands[0]["bytes"] == 2):
                isize |= 0b1
    #print (1 + (reg1 == "SP") * ((True == (isize & 0b1))+1) + (reg2 == "SP") * ((True == (isize & 0b10))+1), op["bytes"])
    
    print(f"case {hex(i)}:\n    puts(\"Operation CB {hex(i)}, {mnemonic}({reg1})({reg2}) not implemented!\");\n    exit(1);\n    break;");
    i += 1;
    

    

    
