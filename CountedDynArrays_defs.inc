{$IFDEF FPC}
  {$MODE ObjFPC}{$H+}
  {$MODESWITCH CLASSICPROCVARS+}
  {$INLINE ON}
  {$DEFINE CanInline}
  {$DEFINE FPC_DisableWarns}
  {$MACRO ON}
{$ELSE}
  {$IF CompilerVersion >= 17 then}  // Delphi 2005+
    {$DEFINE CanInline}
  {$ELSE}
    {$UNDEF CanInline}
  {$IFEND}
{$ENDIF}

//------------------------------------------------------------------------------
// do not touch following...

{$UNDEF CDA_Interface}
{$UNDEF CDA_IMplemantation}

{$UNDEF CDA_DisableFunc_ItemCompareFunc}
{$UNDEF CDA_DisableFunc_ItemExchangeFunc}

{$UNDEF CDA_DisableFunc_Length}
{$UNDEF CDA_DisableFunc_Capacity}
{$UNDEF CDA_DisableFunc_FreeCapacity}
{$UNDEF CDA_DisableFunc_Count}

{$UNDEF CDA_DisableFunc_Low}
{$UNDEF CDA_DisableFunc_High}
{$UNDEF CDA_DisableFunc_CheckIndex}

{$UNDEF CDA_DisableFunc_Init}
{$UNDEF CDA_DisableFunc_SetLength}
{$UNDEF CDA_DisableFunc_SetCapacity}

{$UNDEF CDA_DisableFunc_Grow}
{$UNDEF CDA_DisableFunc_Shrink}

{$UNDEF CDA_DisableFunc_UniqueArray}
{$UNDEF CDA_DisableFunc_CopyP}
{$UNDEF CDA_DisableFunc_Copy}

{$UNDEF CDA_DisableFunc_GetData}
{$UNDEF CDA_DisableFunc_SetData}

{$UNDEF CDA_DisableFunc_GetItem}
{$UNDEF CDA_DisableFunc_SetItem}

{$UNDEF CDA_DisableFunc_First}
{$UNDEF CDA_DisableFunc_Last}

{$UNDEF CDA_DisableFunc_IndexOf}
{$UNDEF CDA_DisableFunc_Add}
{$UNDEF CDA_DisableFunc_Insert}
{$UNDEF CDA_DisableFunc_Exchange}
{$UNDEF CDA_DisableFunc_Move}
{$UNDEF CDA_DisableFunc_Remove}
{$UNDEF CDA_DisableFunc_Delete}
{$UNDEF CDA_DisableFunc_Clear}

{$UNDEF CDA_DisableFunc_Same}
{$UNDEF CDA_DisableFunc_Reverse}
{$UNDEF CDA_DisableFunc_Sort}

