{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Compilation symbols, switches and parameters.

  Version 1.4.2 (2024-05-03)

  Last changed 2024-10-04

  ©2018-2024 František Milt

  Contacts:
    František Milt: frantisek.milt@gmail.com

  Support:
    If you find this code useful, please consider supporting its author(s) by
    making a small donation using the following link(s):

      https://www.paypal.me/FMilt

  Changelog:
    For detailed changelog and history please refer to this git repository:

      github.com/TheLazyTomcat/CountedDynArrays

  Dependencies:
  * AuxExceptions   - github.com/TheLazyTomcat/Lib.AuxExceptions
    AuxTypes        - github.com/TheLazyTomcat/Lib.AuxTypes
    BinaryStreaming - github.com/TheLazyTomcat/Lib.BinaryStreaming
    ListSorters     - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect         - github.com/TheLazyTomcat/Lib.StrRect

  Library AuxExceptions is required only when rebasing local exception classes
  (see symbol CountedDynArrays_UseAuxExceptions for details).

  Library AuxExceptions might also be required as an indirect dependency.

  Indirect dependencies:
    AuxClasses  - github.com/TheLazyTomcat/Lib.AuxClasses
    SimpleCPUID - github.com/TheLazyTomcat/Lib.SimpleCPUID
    UInt64Utils - github.com/TheLazyTomcat/Lib.UInt64Utils
    WinFileInfo - github.com/TheLazyTomcat/Lib.WinFileInfo

===============================================================================}
{!tun_end!} // ignore this line
{
  CountedDynArrays_UseAuxExceptions

  If you want library-specific exceptions to be based on more advanced classes
  provided by AuxExceptions library instead of basic Exception class, and don't
  want to or cannot change code in this unit, you can define global symbol
  CountedDynArrays_UseAuxExceptions to achieve this.
}
{$IF Defined(CountedDynArrays_UseAuxExceptions)}
  {$DEFINE UseAuxExceptions}
{$IFEND}

//------------------------------------------------------------------------------

{$IF defined(CPU64) or defined(CPU64BITS)}
  {$DEFINE CPU64bit}
{$ELSEIF defined(CPU16)}
  {$DEFINE CPU16bit}
{$ELSE}
  {$DEFINE CPU32bit}
{$IFEND}

{$IFDEF FPC}
  {$MODE ObjFPC}
  {$MODESWITCH CLASSICPROCVARS+}
  {$INLINE ON}
  {$DEFINE CanInline}
  {$DEFINE FPC_DisableWarns}
  {$MACRO ON}
{$ELSE}
  {$IF CompilerVersion >= 17} // Delphi 2005+
    {$DEFINE CanInline}
  {$ELSE}
    {$UNDEF CanInline}
  {$IFEND}
{$ENDIF}
{$H+}

//------------------------------------------------------------------------------
// do not touch following defines...

{$UNDEF CDA_Structure}
{$UNDEF CDA_Interface}
{$UNDEF CDA_Implemantation}

{$UNDEF CDA_ConstBaseType}
{$UNDEF CDA_CaseSensitiveBaseType}

{$UNDEF CDA_FuncNamePrefix}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$UNDEF CDA_FuncOverride_ItemInit}
{$UNDEF CDA_FuncOverride_ItemFinal}
{$UNDEF CDA_FuncOverride_ItemUnique}
{$UNDEF CDA_FuncOverride_ItemCompare}
{$UNDEF CDA_FuncOverride_ItemWrite}
{$UNDEF CDA_FuncOverride_ItemRead}

{$UNDEF CDA_FuncOverride_SortFunc_ItemCompare}
{$UNDEF CDA_FuncOverride_SortFunc_ItemCompareStabilized}
{$UNDEF CDA_FuncOverride_SortFunc_ItemExchange}
{$UNDEF CDA_FuncOverride_SortFunc_ItemExchangeStabilized}

{$UNDEF CDA_FuncOverride_Valid}
{$UNDEF CDA_FuncOverride_Validate}
{$UNDEF CDA_FuncOverride_Init}
{$UNDEF CDA_FuncOverride_Final}

{$UNDEF CDA_FuncOverride_GetUserData}
{$UNDEF CDA_FuncOverride_SetUserData}

{$UNDEF CDA_FuncOverride_Length}
{$UNDEF CDA_FuncOverride_Capacity}
{$UNDEF CDA_FuncOverride_CapacityFree}
{$UNDEF CDA_FuncOverride_Count}

{$UNDEF CDA_FuncOverride_SetLength}
{$UNDEF CDA_FuncOverride_SetCapacity}
{$UNDEF CDA_FuncOverride_SetCount}

{$UNDEF CDA_FuncOverride_Grow}
{$UNDEF CDA_FuncOverride_Shrink}

{$UNDEF CDA_FuncOverride_UniqueArray}
{$UNDEF CDA_FuncOverride_CopyC}
{$UNDEF CDA_FuncOverride_Copy}

{$UNDEF CDA_FuncOverride_Low}
{$UNDEF CDA_FuncOverride_High}
{$UNDEF CDA_FuncOverride_CheckIndex}

{$UNDEF CDA_FuncOverride_GetItem}
{$UNDEF CDA_FuncOverride_GetItemPtr}
{$UNDEF CDA_FuncOverride_SetItem}

{$UNDEF CDA_FuncOverride_First}
{$UNDEF CDA_FuncOverride_Last}
{$UNDEF CDA_FuncOverride_FirstPtr}
{$UNDEF CDA_FuncOverride_LastPtr}

{$UNDEF CDA_FuncOverride_IndexOf}
{$UNDEF CDA_FuncOverride_Find}
{$UNDEF CDA_FuncOverride_Add}
{$UNDEF CDA_FuncOverride_Append}
{$UNDEF CDA_FuncOverride_Insert}
{$UNDEF CDA_FuncOverride_Exchange}
{$UNDEF CDA_FuncOverride_Move}
{$UNDEF CDA_FuncOverride_Extract}
{$UNDEF CDA_FuncOverride_Remove}
{$UNDEF CDA_FuncOverride_Delete}
{$UNDEF CDA_FuncOverride_Clear}

{$UNDEF CDA_FuncOverride_ArrayPtr}
{$UNDEF CDA_FuncOverride_Compare}
{$UNDEF CDA_FuncOverride_Same}
{$UNDEF CDA_FuncOverride_Reverse}
{$UNDEF CDA_FuncOverride_Sort}
{$UNDEF CDA_FuncOverride_SortStabilized}

{$UNDEF CDA_FuncOverride_WriteToStream}
{$UNDEF CDA_FuncOverride_SaveToStream}
{$UNDEF CDA_FuncOverride_ReadFromStream}
{$UNDEF CDA_FuncOverride_LoadFromStream}
{$UNDEF CDA_FuncOverride_WriteToFile}
{$UNDEF CDA_FuncOverride_ReadFromFile}
{$UNDEF CDA_FuncOverride_SaveToFile}
{$UNDEF CDA_FuncOverride_LoadFromFile}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$UNDEF CDA_FuncReintroduce_ItemInit}
{$UNDEF CDA_FuncReintroduce_ItemFinal}
{$UNDEF CDA_FuncReintroduce_ItemUnique}
{$UNDEF CDA_FuncReintroduce_ItemCompare}
{$UNDEF CDA_FuncReintroduce_ItemWrite}
{$UNDEF CDA_FuncReintroduce_ItemRead}

{$UNDEF CDA_FuncReintroduce_SortFunc_ItemCompare}
{$UNDEF CDA_FuncReintroduce_SortFunc_ItemCompareStabilized}
{$UNDEF CDA_FuncReintroduce_SortFunc_ItemExchange}
{$UNDEF CDA_FuncReintroduce_SortFunc_ItemExchangeStabilized}

{$UNDEF CDA_FuncReintroduce_Valid}
{$UNDEF CDA_FuncReintroduce_Validate}
{$UNDEF CDA_FuncReintroduce_Init}
{$UNDEF CDA_FuncReintroduce_Final}

{$UNDEF CDA_FuncReintroduce_GetUserData}
{$UNDEF CDA_FuncReintroduce_SetUserData}

{$UNDEF CDA_FuncReintroduce_Length}
{$UNDEF CDA_FuncReintroduce_Capacity}
{$UNDEF CDA_FuncReintroduce_CapacityFree}
{$UNDEF CDA_FuncReintroduce_Count}

{$UNDEF CDA_FuncReintroduce_SetLength}
{$UNDEF CDA_FuncReintroduce_SetCapacity}
{$UNDEF CDA_FuncReintroduce_SetCount}

{$UNDEF CDA_FuncReintroduce_Grow}
{$UNDEF CDA_FuncReintroduce_Shrink}

{$UNDEF CDA_FuncReintroduce_UniqueArray}
{$UNDEF CDA_FuncReintroduce_CopyC}
{$UNDEF CDA_FuncReintroduce_Copy}

{$UNDEF CDA_FuncReintroduce_Low}
{$UNDEF CDA_FuncReintroduce_High}
{$UNDEF CDA_FuncReintroduce_CheckIndex}

{$UNDEF CDA_FuncReintroduce_GetItem}
{$UNDEF CDA_FuncReintroduce_GetItemPtr}
{$UNDEF CDA_FuncReintroduce_SetItem}

{$UNDEF CDA_FuncReintroduce_First}
{$UNDEF CDA_FuncReintroduce_Last}
{$UNDEF CDA_FuncReintroduce_FirstPtr}
{$UNDEF CDA_FuncReintroduce_LastPtr}

{$UNDEF CDA_FuncReintroduce_IndexOf}
{$UNDEF CDA_FuncReintroduce_Find}
{$UNDEF CDA_FuncReintroduce_Add}
{$UNDEF CDA_FuncReintroduce_Append}
{$UNDEF CDA_FuncReintroduce_Insert}
{$UNDEF CDA_FuncReintroduce_Exchange}
{$UNDEF CDA_FuncReintroduce_Move}
{$UNDEF CDA_FuncReintroduce_Extract}
{$UNDEF CDA_FuncReintroduce_Remove}
{$UNDEF CDA_FuncReintroduce_Delete}
{$UNDEF CDA_FuncReintroduce_Clear}

{$UNDEF CDA_FuncReintroduce_ArrayPtr}
{$UNDEF CDA_FuncReintroduce_Compare}
{$UNDEF CDA_FuncReintroduce_Same}
{$UNDEF CDA_FuncReintroduce_Reverse}
{$UNDEF CDA_FuncReintroduce_Sort}
{$UNDEF CDA_FuncReintroduce_SortStabilized}

{$UNDEF CDA_FuncReintroduce_WriteToStream}
{$UNDEF CDA_FuncReintroduce_SaveToStream}
{$UNDEF CDA_FuncReintroduce_ReadFromStream}
{$UNDEF CDA_FuncReintroduce_LoadFromStream}
{$UNDEF CDA_FuncReintroduce_WriteToFile}
{$UNDEF CDA_FuncReintroduce_ReadFromFile}
{$UNDEF CDA_FuncReintroduce_SaveToFile}
{$UNDEF CDA_FuncReintroduce_LoadFromFile}
