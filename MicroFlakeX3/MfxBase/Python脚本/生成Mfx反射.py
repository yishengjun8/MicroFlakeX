Funcion = [
    'Init',
    'GetD2D1RectU',
    'GetD2D1SizeU',
    'GetD2D1PointU',
    'GetD2D1RectF',
    'GetD2D1SizeF',
    'GetD2D1PointF',
    'SetSize',
    'SetPoint',
    'SetX',
    'SetY',
    'SetWidth',
    'SetHeight',
    'SetTop',
    'SetLeft',
    'SetRight',
    'SetBottom',
    'GetSize',
    'GetPoint',
    'GetX',
    'GetY',
    'GetWidth',
    'GetHeight',
    'GetTop',
    'GetLeft',
    'GetRight',
    'GetBottom',
    'Empty',
    'Offset',
    'Inflate',
    'Collision',
    'PointInside',
    'END',

    ]



MfxObject = 'MfxRect'
MfxFather = "MfxType"

print('MfxObject_Init_0(' + MfxObject + ')')

print('MfxObject_Init_1(' + MfxObject + ', ' + Funcion[0] + ')')

for i in range(len(Funcion)-1):
    print('MfxAutoFunc_1(' + MfxObject + ', ' + Funcion[i] + ', ' + Funcion[i+1] + ')')
    
print('MfxObject_Init_2(' + MfxObject + ', ' + MfxFather + ')')
    
