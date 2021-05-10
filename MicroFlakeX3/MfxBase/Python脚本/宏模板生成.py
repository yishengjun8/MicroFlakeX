
'''
i = 3
a = 1
while i < 128:
    print("#define MFX_AUTOFUNC_DO_NUMMAP_" + str(i) + " " + str(a))
    print("")
    i = i+2
    a = a+1
'''


for i in range(126):
    print("#define MfxAutoFunc_Enum_" + str(i+1) + "(OBJ, NUM_1, FUNC_1, NUM_2, FUNC_2, ...)\\")
    print("    MfxAutoFunc_Connect(OBJ, NUM_1, FUNC_1, FUNC_2)\\")
    print("    CONNECT(MfxAutoFunc_Enum_" + str(i) + "(OBJ, NUM_2, FUNC_2, __VA_ARGS__))")
    print("")

    

    
