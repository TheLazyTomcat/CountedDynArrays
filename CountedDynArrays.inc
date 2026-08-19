{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Main implementation template

  Version 1.5.2 (2026-08-15)

  Last changed 2026-08-15

  ©2018-2026 František Milt

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
    ListUtils       - github.com/TheLazyTomcat/Lib.ListUtils
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

{===============================================================================
--------------------------------------------------------------------------------
    Main record structure (common to all types)
--------------------------------------------------------------------------------
===============================================================================}

{$IFDEF CDA_Structure}
    Signature:    TCDASignature;
    Arr:          array of TCDABaseType;
    Count:        Integer;
    UserData:     PtrInt;
    InternalPtr:  Pointer;
    InternalInt:  PtrInt;
    Checksum:     TCDAChecksum;
{$ENDIF}

{===============================================================================
--------------------------------------------------------------------------------
    Interface section (declarations of functions)
--------------------------------------------------------------------------------
===============================================================================}

{$IFDEF CDA_Interface}

// internal structure manipulation
{$IFNDEF CDA_FuncReintroduce_Valid}
  Function CDA_Valid(const Arr: TCDAArrayType): Boolean; overload;{$IF Defined(CanInline) and Defined(FPC)} inline;{$IFEND}{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Validate}
  Function CDA_Validate(var Arr: TCDAArrayType): Boolean; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Init}
  procedure CDA_Init(out Arr: TCDAArrayType); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Final}
  procedure CDA_Final(var Arr: TCDAArrayType); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Invalidate}
  procedure CDA_Invalidate(var Arr: TCDAArrayType); overload;{$ENDIF}

// user data access
{$IFNDEF CDA_FuncReintroduce_GetUserData}
  Function CDA_GetUserData(const Arr: TCDAArrayType): PtrInt; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_SetUserData}
  procedure CDA_SetUserData(var Arr: TCDAArrayType; UserData: PtrInt); overload;{$ENDIF}

// capacity and count access
{$IFNDEF CDA_FuncReintroduce_Length}
  Function CDA_Length(const Arr: TCDAArrayType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Capacity}
  Function CDA_Capacity(const Arr: TCDAArrayType): Integer; overload;{$IFDEF CanInline} inline;{$ENDIF}{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_CapacityFree}
  Function CDA_CapacityFree(const Arr: TCDAArrayType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_FreeCapacity}
  Function CDA_FreeCapacity(const Arr: TCDAArrayType): Integer; overload;{$IFDEF CanInline} inline;{$ENDIF}{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Count}
  Function CDA_Count(const Arr: TCDAArrayType): Integer; overload;{$ENDIF}

// explicit changing of capacity and count
{$IFNDEF CDA_FuncReintroduce_SetLength}
  procedure CDA_SetLength(var Arr: TCDAArrayType; NewLength: Integer); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_SetCapacity}
  procedure CDA_SetCapacity(var Arr: TCDAArrayType; NewCapacity: Integer); overload;{$IFDEF CanInline} inline;{$ENDIF}{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_SetCount}
  procedure CDA_SetCount(var Arr: TCDAArrayType; NewCount: Integer); overload;{$ENDIF}

// implicit changing of capacity
{$IFNDEF CDA_FuncReintroduce_Grow}
  procedure CDA_Grow(var Arr: TCDAArrayType; GrowSettings: TGrowSettings; MinSpace: Integer = 1); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_GrowDef}
  procedure CDA_Grow(var Arr: TCDAArrayType; MinSpace: Integer = 1); overload;{$IF Defined(CanInline) and not Defined(FPC)} inline;{$IFEND}{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Shrink}
  procedure CDA_Shrink(var Arr: TCDAArrayType; ShrinkSettings: TShrinkSettings); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_ShrinkDef}
  procedure CDA_Shrink(var Arr: TCDAArrayType); overload;{$IF Defined(CanInline) and not Defined(FPC)} inline;{$IFEND}{$ENDIF}

// secure copy
{$IFNDEF CDA_FuncReintroduce_UniqueArray}
  procedure CDA_UniqueArray(var Arr: TCDAArrayType); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Copy}
  Function CDA_Copy(const Src: TCDAArrayType; Index, Count: Integer): TCDAArrayType; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_CopyAll}
  Function CDA_Copy(const Src: TCDAArrayType): TCDAArrayType; overload;{$ENDIF}

// indices functions
{$IFNDEF CDA_FuncReintroduce_Low}
  Function CDA_Low(const Arr: TCDAArrayType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_High}
  Function CDA_High(const Arr: TCDAArrayType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_CheckIndex}
  Function CDA_CheckIndex(const Arr: TCDAArrayType; Index: Integer): Boolean; overload;{$ENDIF}

// item access
{$IFNDEF CDA_FuncReintroduce_GetItem}
  Function CDA_GetItem(const Arr: TCDAArrayType; Index: Integer; SecureCopy: Boolean = False): TCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_GetItemPtr}
  Function CDA_GetItemPtr(const Arr: TCDAArrayType; Index: Integer): PCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_SetItem}
  procedure CDA_SetItem(var Arr: TCDAArrayType; Index: Integer;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False); overload;{$ENDIF}

// ensuring uniqueness of item(s)
{$IFNDEF CDA_FuncReintroduce_UniqueItem}
  procedure CDA_UniqueItem(var Arr: TCDAArrayType; Index: Integer); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_UniqueItems}
  procedure CDA_UniqueItems(var Arr: TCDAArrayType; FromIndex, ToIndex: Integer); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_UniqueItemsAll}
  procedure CDA_UniqueItems(var Arr: TCDAArrayType); overload;{$ENDIF}

// special items access
{$IFNDEF CDA_FuncReintroduce_First}
  Function CDA_First(const Arr: TCDAArrayType; SecureCopy: Boolean = False): TCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Last}
  Function CDA_Last(const Arr: TCDAArrayType; SecureCopy: Boolean = False): TCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_FirstPtr}
  Function CDA_FirstPtr(const Arr: TCDAArrayType): PCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_LastPtr}
  Function CDA_LastPtr(const Arr: TCDAArrayType): PCDABaseType; overload;{$ENDIF}

// list-like funtions
{$IFNDEF CDA_FuncReintroduce_Contains}
  Function CDA_Contains(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_IndexOf}
  Function CDA_IndexOf(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Find}
  Function CDA_Find(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Add}
  Function CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_AddDup}
  Function CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; Duplicates: TDuplicates{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}; SecureCopy: Boolean = False): Integer; overload;{$IFDEF CanInline} inline;{$ENDIF}{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_AddDupBool}
  Function CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer; Duplicates: TDuplicates{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}; SecureCopy: Boolean = False): Boolean; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Append}
  procedure CDA_Append(var Arr: TCDAArrayType; const Items: TCDAArrayType; SecureCopy: Boolean = False); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Insert}
  procedure CDA_Insert(var Arr: TCDAArrayType; Index: Integer;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Exchange}
  procedure CDA_Exchange(var Arr: TCDAArrayType; Idx1, Idx2: Integer); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Move}
  procedure CDA_Move(var Arr: TCDAArrayType; SrcIdx, DstIdx: Integer); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Extract}
  Function CDA_Extract(var Arr: TCDAArrayType; Index: Integer): TCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Remove}
  Function CDA_Remove(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_RemoveBool}
  Function CDA_Remove(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_RemoveAll}
  Function CDA_RemoveAll(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Delete}
  procedure CDA_Delete(var Arr: TCDAArrayType; Index: Integer); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Clear}
  procedure CDA_Clear(var Arr: TCDAArrayType); overload;{$ENDIF}

// whole-array access/operation
{$IFNDEF CDA_FuncReintroduce_ArrayPtr}
  Function CDA_ArrayPtr(const Arr: TCDAArrayType): Pointer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Compare}
  Function CDA_Compare(const Arr1, Arr2: TCDAArrayType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Same}
  Function CDA_Same(const Arr1, Arr2: TCDAArrayType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean; overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Reverse}
  procedure CDA_Reverse(var Arr: TCDAArrayType); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Sort}
  procedure CDA_Sort(var Arr: TCDAArrayType; Reversed: Boolean = False{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_SortStabilized}
  procedure CDA_SortStabilized(var Arr: TCDAArrayType; Reversed: Boolean = False{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_FillFrom}
  procedure CDA_FillFrom(var Arr: TCDAArrayType; Index: Integer; SecureCopy: Boolean = False); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_Fill}
  procedure CDA_Fill(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False); overload;{$ENDIF}

// streaming (stream)
{$IFNDEF CDA_FuncReintroduce_WriteToStream}
  procedure CDA_WriteToStream(const Arr: TCDAArrayType; Stream: TStream); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_SaveToStream}
  procedure CDA_SaveToStream(const Arr: TCDAArrayType; Stream: TStream); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_ReadFromStream}
  procedure CDA_ReadFromStream(var Arr: TCDAArrayType; Stream: TStream); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_LoadFromStream}
  procedure CDA_LoadFromStream(var Arr: TCDAArrayType; Stream: TStream); overload;{$ENDIF}

// streaming (file)
{$IFNDEF CDA_FuncReintroduce_WriteToFile}
  procedure CDA_WriteToFile(const Arr: TCDAArrayType; const FileName: String); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_SaveToFile}
  procedure CDA_SaveToFile(const Arr: TCDAArrayType; const FileName: String); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_ReadFromFile}
  procedure CDA_ReadFromFile(var Arr: TCDAArrayType; const FileName: String); overload;{$ENDIF}
{$IFNDEF CDA_FuncReintroduce_LoadFromFile}                                               
  procedure CDA_LoadFromFile(var Arr: TCDAArrayType; const FileName: String); overload;{$ENDIF}

{$ENDIF}

{===============================================================================
--------------------------------------------------------------------------------
    Implementation section (implementation of functions)
--------------------------------------------------------------------------------
===============================================================================}

{$IFDEF CDA_Implementation}

{===============================================================================
    Auxiliary internal functions (cannot be overriden or reintroduced)
===============================================================================}

Function CDA_Signature: TCDASignature;
begin
{$IFDEF CPU64bit}
Result := (PtrUInt(Random($10000)) shl 48) or (PtrUInt(Random($10000)) shl 32) or
          (PtrUInt(Random($10000)) shl 16) or PtrUInt(Random($10000)) ;
{$ELSE}
Result := (PtrUInt(Random($10000)) shl 16) or PtrUInt(Random($10000));
{$ENDIF}
end;

//------------------------------------------------------------------------------

Function CDA_Checksum(const Arr: TCDAArrayType): TCDAChecksum;
var
  ArrayPointer:         Pointer;
  ArrayPointerOverlay:  PtrUInt absolute ArrayPointer;
begin
{
  Checksum is obtained by only XOR-ing of some (inverted) fields. Field Arr is
  by compiler implemented as a pointer to the dynamic array itself, so we can
  use it as such.
}
ArrayPointer := Pointer(Arr.Arr);
Result := Arr.Signature xor ArrayPointerOverlay xor not(PtrUInt(Arr.Count))
end;

{===============================================================================
    Internal functions
===============================================================================}

{$IF Defined(CDA_FuncOverride_ItemInit) or Defined(CDA_FuncReintroduce_ItemInit)}
procedure _CDA_ItemInit(var Item: TCDABaseType);
{$ELSE}
procedure CDA_ItemInit(var Item: TCDABaseType);
{$IFEND}
begin
Item := CDA_DEFAULT_VALUE;
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_ItemFinal) or Defined(CDA_FuncReintroduce_ItemFinal)}
procedure _CDA_ItemFinal(var Item: TCDABaseType);
{$ELSE}
procedure CDA_ItemFinal(var Item: TCDABaseType);
{$IFEND}
begin
Item := CDA_DEFAULT_VALUE;
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_ItemUnique) or Defined(CDA_FuncReintroduce_ItemUnique)}
procedure _CDA_ItemUnique(var Item: TCDABaseType);
{$ELSE}
procedure CDA_ItemUnique(var Item: TCDABaseType);
{$IFEND}
begin
Item := Item; // should result in no-op
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_ItemCompare) or Defined(CDA_FuncReintroduce_ItemCompare)}
Function _CDA_ItemCompare({$IFDEF CDA_ConstBaseType}const {$ENDIF}A,B: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean{$ENDIF}): Integer;
{$ELSE}
Function CDA_ItemCompare({$IFDEF CDA_ConstBaseType}const {$ENDIF}A,B: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean{$ENDIF}): Integer;
{$IFEND}
begin
{
  WARNING -  following code is nonsensical and serves only as a placeholder to
             suppress warnings produced by compilers about unused parameters,
             it must be replaced by proper code suited for the actual item type.
}
If not Assigned(Addr(A)) and not Assigned(Addr(B))
{$IFDEF CDA_CaseSensitiveBaseType} and CaseSensitive {$ENDIF} then
  Result := 0
else
  Result := 0;
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_ItemWrite) or Defined(CDA_FuncReintroduce_ItemWrite)}
procedure _CDA_ItemWrite({$IFDEF CDA_ConstBaseType}const {$ENDIF}Item: TCDABaseType; Stream: TStream);
{$ELSE}
procedure CDA_ItemWrite({$IFDEF CDA_ConstBaseType}const {$ENDIF}Item: TCDABaseType; Stream: TStream);
{$IFEND}
begin
{
  WARNING -  following code is nonsensical and serves only as a placeholder to
             suppress warnings produced by compilers about unused parameters,
             it must be replaced by proper code suited for the actual item type.
}
If not Assigned(Addr(Item)) then
  Stream.Seek(0,soCurrent);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_ItemRead) or Defined(CDA_FuncReintroduce_ItemRead)}
Function _CDA_ItemRead(Stream: TStream): TCDABaseType;
{$ELSE}
Function CDA_ItemRead(Stream: TStream): TCDABaseType;
{$IFEND}
begin
{
  WARNING -  following code is nonsensical and serves only as a placeholder to
             suppress warnings produced by compilers about unused parameters,
             it must be replaced by proper code suited for the actual item type.
}
Stream.Seek(0,soCurrent);
Result := CDA_DEFAULT_VALUE;
end;

//==============================================================================

{$IF Defined(CDA_FuncOverride_SortFunc_ItemCompare) or Defined(CDA_FuncReintroduce_SortFunc_ItemCompare)}
Function _CDA_SortFunc_ItemCompare(Context: Pointer; Idx1,Idx2: Integer): Integer;{$IFDEF CanInline} inline;{$ENDIF}
{$ELSE}
Function CDA_SortFunc_ItemCompare(Context: Pointer; Idx1,Idx2: Integer): Integer;{$IFDEF CanInline} inline;{$ENDIF}
{$IFEND}
begin
{$IFDEF CDA_CaseSensitiveBaseType}
Result := CDA_ItemCompare(TCDAArrayType(Context^).Arr[Idx1],TCDAArrayType(Context^).Arr[Idx2],TCDAArrayType(Context^).InternalInt <> 0);
{$ELSE}
Result := CDA_ItemCompare(TCDAArrayType(Context^).Arr[Idx1],TCDAArrayType(Context^).Arr[Idx2]);
{$ENDIF}
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SortFunc_ItemCompareStabilized) or Defined(CDA_FuncReintroduce_SortFunc_ItemCompareStabilized)}
Function _CDA_SortFunc_ItemCompareStabilized(Context: Pointer; Idx1,Idx2: Integer): Integer;
{$ELSE}
Function CDA_SortFunc_ItemCompareStabilized(Context: Pointer; Idx1,Idx2: Integer): Integer;
{$IFEND}
begin
Result := CDA_SortFunc_ItemCompare(Context,Idx1,Idx2);
If Result = 0 then
  with TCDAArrayType(Context^) do
    begin
      If PCDAIndexArray(InternalPtr)^[Idx1] < PCDAIndexArray(InternalPtr)^[Idx2] then
        Result := -1
      else If PCDAIndexArray(InternalPtr)^[Idx1] > PCDAIndexArray(InternalPtr)^[Idx2] then
        Result := +1;
    end;
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SortFunc_ItemExchange) or Defined(CDA_FuncReintroduce_SortFunc_ItemExchange)}
procedure _CDA_SortFunc_ItemExchange(Context: Pointer; Idx1,Idx2: Integer);{$IFDEF CanInline} inline;{$ENDIF}
{$ELSE}
procedure CDA_SortFunc_ItemExchange(Context: Pointer; Idx1,Idx2: Integer);{$IFDEF CanInline} inline;{$ENDIF}
{$IFEND}
begin
CDA_Exchange(TCDAArrayType(Context^),Idx1,Idx2);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SortFunc_ItemExchangeStabilized) or Defined(CDA_FuncReintroduce_SortFunc_ItemExchangeStabilized)}
procedure _CDA_SortFunc_ItemExchangeStabilized(Context: Pointer; Idx1,Idx2: Integer);
{$ELSE}
procedure CDA_SortFunc_ItemExchangeStabilized(Context: Pointer; Idx1,Idx2: Integer);
{$IFEND}
var
  Temp: Integer;
begin
CDA_SortFunc_ItemExchange(Context,Idx1,Idx2);
with TCDAArrayType(Context^) do
  begin
    Temp := PCDAIndexArray(InternalPtr)^[Idx1];
    PCDAIndexArray(InternalPtr)^[Idx1] := PCDAIndexArray(InternalPtr)^[Idx2];
    PCDAIndexArray(InternalPtr)^[Idx2] := Temp;
  end;
end;

{===============================================================================
    Public functions
===============================================================================}

{$IF Defined(CDA_FuncOverride_Valid) or Defined(CDA_FuncReintroduce_Valid)}
Function _CDA_Valid(const Arr: TCDAArrayType): Boolean;
{$ELSE}
Function CDA_Valid(const Arr: TCDAArrayType): Boolean;
{$IFEND}
begin
Result := Arr.Checksum = CDA_Checksum(Arr);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Validate) or Defined(CDA_FuncReintroduce_Validate)}
Function _CDA_Validate(var Arr: TCDAArrayType): Boolean;
{$ELSE}
Function CDA_Validate(var Arr: TCDAArrayType): Boolean;
{$IFEND}
begin
Result := CDA_Valid(Arr);
If not Result then
  CDA_Init(Arr);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Init) or Defined(CDA_FuncReintroduce_Init)}
procedure _CDA_Init(out Arr: TCDAArrayType);
{$ELSE}
procedure CDA_Init(out Arr: TCDAArrayType);
{$IFEND}
begin
Arr.Signature := CDA_Signature;
Arr.Arr := nil; // if the array is not empty this will free it automatically
Arr.Count := 0;
Arr.UserData := 0;
Arr.InternalPtr := nil;
Arr.InternalInt := 0;
Arr.Checksum := CDA_Checksum(Arr);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Init) or Defined(CDA_FuncReintroduce_Init)}
procedure _CDA_Final(var Arr: TCDAArrayType);
{$ELSE}
procedure CDA_Final(var Arr: TCDAArrayType);
{$IFEND}
var
  i:  Integer;
begin
If CDA_Valid(Arr) then
  For i := 0 to Pred(Arr.Count) do
    CDA_ItemFinal(Arr.Arr[i]);
CDA_Invalidate(Arr);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Invalidate) or Defined(CDA_FuncReintroduce_Invalidate)}
procedure _CDA_Invalidate(var Arr: TCDAArrayType);
{$ELSE}
procedure CDA_Invalidate(var Arr: TCDAArrayType);
{$IFEND}
begin
Arr.Signature := 0;
Arr.Arr := nil;
Arr.Count := 0;
Arr.UserData := 0;
Arr.InternalPtr := nil;
Arr.InternalInt := 0;
Arr.Checksum := not CDA_Checksum(Arr);
end;

//==============================================================================
  
{$IF Defined(CDA_FuncOverride_GetUserData) or Defined(CDA_FuncReintroduce_GetUserData)}
Function _CDA_GetUserData(const Arr: TCDAArrayType): PtrInt;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_GetUserData(const Arr: TCDAArrayType): PtrInt;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_GetUserData(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Result := Arr.UserData;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SetUserData) or Defined(CDA_FuncReintroduce_SetUserData)}
procedure _CDA_SetUserData(var Arr: TCDAArrayType; UserData: PtrInt);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_SetUserData(var Arr: TCDAArrayType; UserData: PtrInt);
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_SetUserData(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Arr.UserData := UserData;
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_Length) or Defined(CDA_FuncReintroduce_Length)}
Function _CDA_Length(const Arr: TCDAArrayType): Integer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Length(const Arr: TCDAArrayType): Integer;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Length(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Result := Length(Arr.Arr);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Capacity) or Defined(CDA_FuncReintroduce_Capacity)}
Function _CDA_Capacity(const Arr: TCDAArrayType): Integer;
{$ELSE}
Function CDA_Capacity(const Arr: TCDAArrayType): Integer;
{$IFEND}
begin
Result := Length(Arr.Arr);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_CapacityFree) or Defined(CDA_FuncReintroduce_CapacityFree)}
Function _CDA_CapacityFree(const Arr: TCDAArrayType): Integer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_CapacityFree(const Arr: TCDAArrayType): Integer;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_CapacityFree(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Result := Length(Arr.Arr) - Arr.Count;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_FreeCapacity) or Defined(CDA_FuncReintroduce_FreeCapacity)}
Function _CDA_FreeCapacity(const Arr: TCDAArrayType): Integer;
{$ELSE}
Function CDA_FreeCapacity(const Arr: TCDAArrayType): Integer;
{$IFEND}
begin
Result := CDA_CapacityFree(Arr);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Count) or Defined(CDA_FuncReintroduce_Count)}
Function _CDA_Count(const Arr: TCDAArrayType): Integer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Count(const Arr: TCDAArrayType): Integer;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Count(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Result := Arr.Count;
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_SetLength) or Defined(CDA_FuncReintroduce_SetLength)}
procedure _CDA_SetLength(var Arr: TCDAArrayType; NewLength: Integer);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_SetLength(var Arr: TCDAArrayType; NewLength: Integer);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_SetLength(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If NewLength < 0 then
  raise ECDAOutOfRange.CreateFmt('%sCDA_SetLength(%s): New length (%d) out of allowed range.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,NewLength]);
If NewLength < Arr.Count then
  For i := NewLength to Pred(Arr.Count) do
    CDA_ItemFinal(Arr.Arr[i]);
SetLength(Arr.Arr,NewLength);
If NewLength < Arr.Count then
  Arr.Count := NewLength;
Arr.Checksum := CDA_Checksum(Arr);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SetCapacity) or Defined(CDA_FuncReintroduce_SetCapacity)}
procedure _CDA_SetCapacity(var Arr: TCDAArrayType; NewCapacity: Integer);
{$ELSE}
procedure CDA_SetCapacity(var Arr: TCDAArrayType; NewCapacity: Integer);
{$IFEND}
begin
CDA_SetLength(Arr,NewCapaCity);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SetCount) or Defined(CDA_FuncReintroduce_SetCount)}
procedure _CDA_SetCount(var Arr: TCDAArrayType; NewCount: Integer);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_SetCount(var Arr: TCDAArrayType; NewCount: Integer);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_SetCount(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If NewCount < 0 then
  raise ECDAOutOfRange.CreateFmt('%sCDA_SetCount(%s): New count (%d) out of allowed range.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,NewCount]);
If NewCount < Arr.Count then
  begin
    // remove existing items
    For i := Pred(Arr.Count) downto NewCount do
      CDA_ItemFinal(Arr.Arr[i]);
    Arr.Count := NewCount;
    CDA_Shrink(Arr);
  end
else If NewCount > Arr.Count then
  begin
    // add new items
    If NewCount > Length(Arr.Arr) then
      CDA_SetCapacity(Arr,NewCount);
    For i := Arr.Count to Pred(NewCount) do
      CDA_ItemInit(Arr.Arr[i]);
    Arr.Count := NewCount;
  end;
Arr.Checksum := CDA_Checksum(Arr);
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_Grow) or Defined(CDA_FuncReintroduce_Grow)}
procedure _CDA_Grow(var Arr: TCDAArrayType; GrowSettings: TGrowSettings; MinSpace: Integer = 1); overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Grow(var Arr: TCDAArrayType; GrowSettings: TGrowSettings; MinSpace: Integer = 1);
{$IFEND}
var
  NewCapacity:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Grow(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If GrowResolve(Length(Arr.Arr),Arr.Count,MinSpace,GrowSettings,NewCapacity) then
  CDA_SetCapacity(Arr,NewCapacity);
end;
{$UNDEF CDA_FuncNamePrefix}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$IF Defined(CDA_FuncOverride_GrowDef) or Defined(CDA_FuncReintroduce_GrowDef)}
procedure _CDA_Grow(var Arr: TCDAArrayType; MinSpace: Integer = 1); overload;
{$ELSE}
procedure CDA_Grow(var Arr: TCDAArrayType; MinSpace: Integer = 1);
{$IFEND}
begin
CDA_Grow(Arr,DefaultGrowSettings,MinSpace);
end;

//------------------------------------------------------------------------------
 
{$IF Defined(CDA_FuncOverride_Shrink) or Defined(CDA_FuncReintroduce_Shrink)}
procedure _CDA_Shrink(var Arr: TCDAArrayType; ShrinkSettings: TShrinkSettings); overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Shrink(var Arr: TCDAArrayType; ShrinkSettings: TShrinkSettings);
{$IFEND}
var
  NewCapacity:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Shrink(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If ShrinkResolve(Length(Arr.Arr),Arr.Count,ShrinkSettings,NewCapacity) then
  CDA_SetCapacity(Arr,NewCapacity);
end;
{$UNDEF CDA_FuncNamePrefix}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$IF Defined(CDA_FuncOverride_ShrinkDef) or Defined(CDA_FuncReintroduce_ShrinkDef)}
procedure _CDA_Shrink(var Arr: TCDAArrayType); overload;
{$ELSE}
procedure CDA_Shrink(var Arr: TCDAArrayType);
{$IFEND}
begin
CDA_Shrink(Arr,DefaultShrinkSettings);
end;

//==============================================================================

{$IF Defined(CDA_FuncOverride_UniqueArray) or Defined(CDA_FuncReintroduce_UniqueArray)}
procedure _CDA_UniqueArray(var Arr: TCDAArrayType);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_UniqueArray(var Arr: TCDAArrayType);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_UniqueArray(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
// alsp change the signature so that the array is truly unique
Arr.Signature := CDA_Signature;
SetLength(Arr.Arr,Length(Arr.Arr));
// ensure individual item are unique
For i := 0 to Pred(Arr.Count) do
  CDA_ItemUnique(Arr.Arr[i]);
Arr.Checksum := CDA_Checksum(Arr);  
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Copy) or Defined(CDA_FuncReintroduce_Copy)}
Function _CDA_Copy(const Src: TCDAArrayType; Index, Count: Integer): TCDAArrayType; overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Copy(const Src: TCDAArrayType; Index, Count: Integer): TCDAArrayType;
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Src) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Copy(%s): Invalid source array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
CDA_Init(Result);
// for index out of range, return an empty array          
If (Index >= 0) and (Index < Src.Count) then
  begin
    If (Index + Count) > Src.Count then
      Count := Src.Count - Index;
    Result.Arr := Copy(Src.Arr,Index,Count);
    Result.Count := Count;
    Result.UserData := Src.UserData;
    For i := 0 to Pred(Result.Count) do
      CDA_ItemUnique(Result.Arr[i]);
    Result.Checksum := CDA_Checksum(Result);
  end;
end;
{$UNDEF CDA_FuncNamePrefix}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$IF Defined(CDA_FuncOverride_CopyAll) or Defined(CDA_FuncReintroduce_CopyAll)}
Function _CDA_Copy(const Src: TCDAArrayType): TCDAArrayType; overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Copy(const Src: TCDAArrayType): TCDAArrayType;
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Src) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Copy(%s): Invalid source array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
CDA_Init(Result);
Result.Arr := Copy(Src.Arr);
Result.Count := Src.Count;
Result.UserData := Src.UserData;
For i := 0 to Pred(Result.Count) do
  CDA_ItemUnique(Result.Arr[i]);
Result.Checksum := CDA_Checksum(Result);
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_Low) or Defined(CDA_FuncReintroduce_Low)}
Function _CDA_Low(const Arr: TCDAArrayType): Integer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Low(const Arr: TCDAArrayType): Integer;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Low(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Result := 0;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------
 
{$IF Defined(CDA_FuncOverride_High) or Defined(CDA_FuncReintroduce_High)}
Function _CDA_High(const Arr: TCDAArrayType): Integer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_High(const Arr: TCDAArrayType): Integer;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_High(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Result := Pred(Arr.Count);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------
 
{$IF Defined(CDA_FuncOverride_CheckIndex) or Defined(CDA_FuncReintroduce_CheckIndex)}
Function _CDA_CheckIndex(const Arr: TCDAArrayType; Index: Integer): Boolean;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_CheckIndex(const Arr: TCDAArrayType; Index: Integer): Boolean;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_CheckIndex(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Result := (Index >= 0) and (Index < Arr.Count);
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_GetItem) or Defined(CDA_FuncReintroduce_GetItem)}
Function _CDA_GetItem(const Arr: TCDAArrayType; Index: Integer; SecureCopy: Boolean = False): TCDABaseType;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_GetItem(const Arr: TCDAArrayType; Index: Integer; SecureCopy: Boolean = False): TCDABaseType;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_GetItem(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Index >= 0) and (Index < Arr.Count) then
  begin
    Result := Arr.Arr[Index];
    If SecureCopy then
      CDA_ItemUnique(Result);
  end
else raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_GetItem(%s): Index (%d) out of bounds.',
             [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Index]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_GetItemPtr) or Defined(CDA_FuncReintroduce_GetItemPtr)}
Function _CDA_GetItemPtr(const Arr: TCDAArrayType; Index: Integer): PCDABaseType;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_GetItemPtr(const Arr: TCDAArrayType; Index: Integer): PCDABaseType;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_GetItemPtr(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Index >= 0) and (Index < Arr.Count) then
  Result := Addr(Arr.Arr[Index])
else
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_GetItemPtr(%s): Index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Index]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------
  
{$IF Defined(CDA_FuncOverride_SetItem) or Defined(CDA_FuncReintroduce_SetItem)}
procedure _CDA_SetItem(var Arr: TCDAArrayType; Index: Integer;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_SetItem(var Arr: TCDAArrayType; Index: Integer;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False);
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_SetItem(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Index >= 0) and (Index < Arr.Count) then
  begin
    CDA_ItemFinal(Arr.Arr[Index]);
    Arr.Arr[Index] := Item;
    If SecureCopy then
      CDA_ItemUnique(Arr.Arr[Index]);
  end
else raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_SetItem(%s): Index (%d) out of bounds.',
             [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Index]);
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_UniqueItem) or Defined(CDA_FuncReintroduce_UniqueItem)}
procedure _CDA_UniqueItem(var Arr: TCDAArrayType; Index: Integer);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_UniqueItem(var Arr: TCDAArrayType; Index: Integer);
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_UniqueItem(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Index >= 0) and (Index < Arr.Count) then
  CDA_ItemUnique(Arr.Arr[Index])
else
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_UniqueItem(%s): Index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Index]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_UniqueItems) or Defined(CDA_FuncReintroduce_UniqueItems)}
procedure _CDA_UniqueItems(var Arr: TCDAArrayType; FromIndex, ToIndex: Integer); overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_UniqueItems(var Arr: TCDAArrayType; FromIndex, ToIndex: Integer);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_UniqueItems(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (FromIndex < 0) or (FromIndex >= Arr.Count) then
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_UniqueItems(%s): From index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,FromIndex]);
If (ToIndex < 0) or (ToIndex >= Arr.Count) then
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_UniqueItems(%s): To index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,ToIndex]);
If FromIndex <= ToIndex then
  For i := FromIndex to ToIndex do
    CDA_ItemUnique(Arr.Arr[i]);
end;
{$UNDEF CDA_FuncNamePrefix}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$IF Defined(CDA_FuncOverride_UniqueItemsAll) or Defined(CDA_FuncReintroduce_UniqueItemsAll)}
procedure _CDA_UniqueItems(var Arr: TCDAArrayType); overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_UniqueItems(var Arr: TCDAArrayType);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_UniqueItems(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
For i := 0 to Pred(Arr.Count) do
  CDA_ItemUnique(Arr.Arr[i]);
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_First) or Defined(CDA_FuncReintroduce_First)}
Function _CDA_First(const Arr: TCDAArrayType; SecureCopy: Boolean = False): TCDABaseType;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_First(const Arr: TCDAArrayType; SecureCopy: Boolean = False): TCDABaseType;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_First(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr.Count > 0 then
  begin
    Result := Arr.Arr[0];
    If SecureCopy then
      CDA_ItemUnique(Result);
  end
else raise ECDAEmptyArray.CreateFmt('%sCDA_First(%s): Array is empty.',
             [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Last) or Defined(CDA_FuncReintroduce_Last)}
Function _CDA_Last(const Arr: TCDAArrayType; SecureCopy: Boolean = False): TCDABaseType;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Last(const Arr: TCDAArrayType; SecureCopy: Boolean = False): TCDABaseType;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Last(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr.Count > 0 then
  begin
    Result := Arr.Arr[Pred(Arr.Count)];
    If SecureCopy then
      CDA_ItemUnique(Result);
  end
else raise ECDAEmptyArray.CreateFmt('%sCDA_Last(%s): Array is empty.',
             [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_FirstPtr) or Defined(CDA_FuncReintroduce_FirstPtr)}
Function _CDA_FirstPtr(const Arr: TCDAArrayType): PCDABaseType;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_FirstPtr(const Arr: TCDAArrayType): PCDABaseType;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_FirstPtr(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr.Count > 0 then
  Result := Addr(Arr.Arr[0])
else
  raise ECDAEmptyArray.CreateFmt('%sCDA_FirstPtr(%s): Array is empty.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------
    
{$IF Defined(CDA_FuncOverride_LastPtr) or Defined(CDA_FuncReintroduce_LastPtr)}
Function _CDA_LastPtr(const Arr: TCDAArrayType): PCDABaseType;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_LastPtr(const Arr: TCDAArrayType): PCDABaseType;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_LastPtr(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr.Count > 0 then
  Result := Addr(Arr.Arr[Pred(Arr.Count)])
else
  raise ECDAEmptyArray.CreateFmt('%sCDA_LastPtr(%s): Array is empty.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_Contains) or Defined(CDA_FuncReintroduce_Contains)}
Function _CDA_Contains(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Contains(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean;
{$IFEND}
var
  i:  Integer;
begin
Result := False;
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Contains(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
For i := 0 to Pred(Arr.Count) do
  If CDA_ItemCompare(Arr.Arr[i],Item{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF}) = 0 then
    begin
      Result := True;
      Break{For i};
    end;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_IndexOf) or Defined(CDA_FuncReintroduce_IndexOf)}
Function _CDA_IndexOf(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_IndexOf(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer;
{$IFEND}
var
  i:  Integer;
begin
Result := -1;
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_IndexOf(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
For i := 0 to Pred(Arr.Count) do
  If CDA_ItemCompare(Arr.Arr[i],Item{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF}) = 0 then
    begin
      Result := i;
      Break{For i};
    end;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Find) or Defined(CDA_FuncReintroduce_Find)}
Function _CDA_Find(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean;
{$ELSE}
Function CDA_Find(const Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean;
{$IFEND}
begin
// CDA_IndexOf checks the array validity
Index := CDA_IndexOf(Arr,Item{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF});
Result := (Index >= 0) and (Index < Arr.Count);
end;

//------------------------------------------------------------------------------
    
{$IF Defined(CDA_FuncOverride_Add) or Defined(CDA_FuncReintroduce_Add)}
Function _CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False): Integer; overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False): Integer;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Add(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
CDA_Grow(Arr);
Result := Arr.Count;
Arr.Arr[Result] := Item;
If SecureCopy then
  CDA_ItemUnique(Arr.Arr[Result]);
Inc(Arr.Count);
Arr.Checksum := CDA_Checksum(Arr);
end;
{$UNDEF CDA_FuncNamePrefix}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$IF Defined(CDA_FuncOverride_AddDup) or Defined(CDA_FuncReintroduce_AddDup)}
Function _CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; Duplicates: TDuplicates{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}; SecureCopy: Boolean = False): Integer; overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; Duplicates: TDuplicates{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}; SecureCopy: Boolean = False): Integer;
{$IFEND}
begin
If not CDA_Add(Arr,Item,Result,Duplicates{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF},SecureCopy) then
  Result := -1;
end;
{$UNDEF CDA_FuncNamePrefix}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$IF Defined(CDA_FuncOverride_AddDupBool) or Defined(CDA_FuncReintroduce_AddDupBool)}
Function _CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer; Duplicates: TDuplicates{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}; SecureCopy: Boolean = False): Boolean; overload;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Add(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer; Duplicates: TDuplicates{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}; SecureCopy: Boolean = False): Boolean;
{$IFEND}
begin
// validity check is done by CDA_Find or CDA_Add, whichever is called first
Result := True;
If Duplicates <> dupAccept then
  begin
    If CDA_Find(Arr,Item,Index{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF}) then
      begin
        If Duplicates = dupError then
          raise ECDADuplicateItem.CreateFmt('%sCDA_Add(%s): Duplicate item.',
            [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
        Result := False;            
      end
    else Index := CDA_Add(Arr,Item,SecureCopy);
  end
else Index := CDA_Add(Arr,Item,SecureCopy);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Append) or Defined(CDA_FuncReintroduce_Append)}
procedure _CDA_Append(var Arr: TCDAArrayType; const Items: TCDAArrayType; SecureCopy: Boolean = False);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Append(var Arr: TCDAArrayType; const Items: TCDAArrayType; SecureCopy: Boolean = False);
{$IFEND}
var
  i,Idx:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Append(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Length(Arr.Arr) < (Arr.Count + Items.Count) then
  CDA_SetCapacity(Arr,Arr.Count + Items.Count);
Idx := Arr.Count;
For i := 0 to Pred(Items.Count) do
  begin
    Arr.Arr[Idx] := Items.Arr[i];
    If SecureCopy then
      CDA_ItemUnique(Arr.Arr[Idx]);
    Inc(Idx);
  end;
Inc(Arr.Count,Items.Count);
Arr.Checksum := CDA_Checksum(Arr);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Insert) or Defined(CDA_FuncReintroduce_Insert)}
procedure _CDA_Insert(var Arr: TCDAArrayType; Index: Integer;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Insert(var Arr: TCDAArrayType; Index: Integer;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Insert(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Index >= 0) and (Index < Arr.Count) then
  begin
    CDA_Grow(Arr);
    For i := Pred(Arr.Count) downto Index do
      Arr.Arr[i + 1] := Arr.Arr[i];
    Arr.Arr[Index] := Item;
    If SecureCopy then
      CDA_ItemUnique(Arr.Arr[Index]);
    Inc(Arr.Count);
    Arr.Checksum := CDA_Checksum(Arr);
  end
else If Index = Arr.Count then
  CDA_Add(Arr,Item)
else
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_Insert(%s): Index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Index]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Exchange) or Defined(CDA_FuncReintroduce_Exchange)}
procedure _CDA_Exchange(var Arr: TCDAArrayType; Idx1, Idx2: Integer);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Exchange(var Arr: TCDAArrayType; Idx1, Idx2: Integer);
{$IFEND}
var
  Temp: TCDABaseType;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Exchange(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Idx1 < 0) or (Idx1 >= Arr.Count) then
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_Exchange(%s): First index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Idx1]);
If (Idx2 < 0) or (Idx2 >= Arr.Count) then
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_Exchange(%s): Second index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Idx2]);
If Idx1 <> Idx2 then
  begin
    Temp := Arr.Arr[Idx1];
    Arr.Arr[Idx1] := Arr.Arr[Idx2];
    Arr.Arr[Idx2] := Temp;
  end;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Move) or Defined(CDA_FuncReintroduce_Move)}
procedure _CDA_Move(var Arr: TCDAArrayType; SrcIdx, DstIdx: Integer);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Move(var Arr: TCDAArrayType; SrcIdx, DstIdx: Integer);
{$IFEND}
var
  Temp: TCDABaseType;
  i:    Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Move(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (SrcIdx < 0) or (SrcIdx >= Arr.Count) then
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_Move(%s): Source index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,SrcIdx]);
If (DstIdx < 0) or (DstIdx >= Arr.Count) then
  raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_Move(%s): Destination index (%d) out of bounds.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,DstIdx]);
If SrcIdx <> DstIdx then
  begin
    Temp := Arr.Arr[SrcIdx];
    If SrcIdx > DstIdx then
      For i := SrcIdx downto Succ(DstIdx) do
        Arr.Arr[i] := Arr.Arr[i - 1]
    else
      For i := SrcIdx to Pred(DstIdx) do
        Arr.Arr[i] := Arr.Arr[i + 1]; 
    Arr.Arr[DstIdx] := Temp;    
  end;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Extract) or Defined(CDA_FuncReintroduce_Extract)}
Function _CDA_Extract(var Arr: TCDAArrayType; Index: Integer): TCDABaseType;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Extract(var Arr: TCDAArrayType; Index: Integer): TCDABaseType;
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Extract(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Index >= 0) and (Index < Arr.count) then
  begin
    // do not call CDA_ItemFinal here
    Result := Arr.Arr[Index];
    For i := Index to (Arr.Count - 2) do
      Arr.Arr[i] := Arr.Arr[i + 1];
    Dec(Arr.Count);
  {
    Following must be before CDA_Shrink because shrink checks the array for
    validity, and since we have changed count, it would fail.
  }
    Arr.Checksum := CDA_Checksum(Arr);
    CDA_Shrink(Arr);
  end
else raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_Extract(%s): Index (%d) out of bounds.',
             [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Index]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Remove) or Defined(CDA_FuncReintroduce_Remove)}
Function _CDA_Remove(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer; overload;
{$ELSE}
Function CDA_Remove(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer;
{$IFEND}
begin
// CDA_Find checks for validity (by extension, it is really done in CDA_IndexOf)
If CDA_Find(Arr,Item,Result{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF}) then
  CDA_Delete(Arr,Result)
else
  Result := -1;
end;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

{$IF Defined(CDA_FuncOverride_RemoveBool) or Defined(CDA_FuncReintroduce_RemoveBool)}
Function _CDA_Remove(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean; overload;
{$ELSE}
Function CDA_Remove(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; out Index: Integer{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean;
{$IFEND}
begin
Result := CDA_Find(Arr,Item,Index{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF});
If Result then
  CDA_Delete(Arr,Index);
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_RemoveAll) or Defined(CDA_FuncReintroduce_RemoveAll)}
Function _CDA_RemoveAll(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_RemoveAll(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer;
{$IFEND}
var
  i,j:  Integer;
begin
// return number of removed items
Result := 0;
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_RemoveAll(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
For i := Pred(Arr.Count) downto 0 do
  If CDA_ItemCompare(Arr.Arr[i],Item{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF}) = 0 then
    begin
      CDA_ItemFinal(Arr.Arr[i]);
      For j := i to (Arr.Count - 2) do
        Arr.Arr[j] := Arr.Arr[j + 1];
      Dec(Arr.Count);
      Inc(Result);
    end;
Arr.Checksum := CDA_Checksum(Arr);
CDA_Shrink(Arr);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------
    
{$IF Defined(CDA_FuncOverride_Delete) or Defined(CDA_FuncReintroduce_Delete)}
procedure _CDA_Delete(var Arr: TCDAArrayType; Index: Integer);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Delete(var Arr: TCDAArrayType; Index: Integer);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Delete(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Index >= 0) and (Index < Arr.Count) then
  begin
    CDA_ItemFinal(Arr.Arr[Index]);
    For i := Index to (Arr.Count - 2) do
      Arr.Arr[i] := Arr.Arr[i + 1];
    Dec(Arr.Count);
    Arr.Checksum := CDA_Checksum(Arr);
    CDA_Shrink(Arr);
  end
else raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_Delete(%s): Index (%d) out of bounds.',
             [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Index]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------
       
{$IF Defined(CDA_FuncOverride_Clear) or Defined(CDA_FuncReintroduce_Clear)}
procedure _CDA_Clear(var Arr: TCDAArrayType);
{$ELSE}
procedure CDA_Clear(var Arr: TCDAArrayType);
{$IFEND}
begin
CDA_SetLength(Arr,0); // does validity check
Arr.UserData := 0;
end;

//==============================================================================

{$IF Defined(CDA_FuncOverride_ArrayPtr) or Defined(CDA_FuncReintroduce_ArrayPtr)}
Function _CDA_ArrayPtr(const Arr: TCDAArrayType): Pointer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_ArrayPtr(const Arr: TCDAArrayType): Pointer;
{$IFEND}
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_ArrayPtr(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr.Count > 0 then
  Result := Addr(Arr.Arr[0])
else
  Result := nil;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Compare) or Defined(CDA_FuncReintroduce_Compare)}
Function _CDA_Compare(const Arr1, Arr2: TCDAArrayType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Compare(const Arr1, Arr2: TCDAArrayType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Integer;
{$IFEND}
var
  i:  Integer;

  Function Min(A,B: Integer): Integer;
  begin
    If A < B then
      Result := A
    else
      Result := B;
  end;

begin
If not CDA_Valid(Arr1) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Compare(%s): Invalid array #1.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If not CDA_Valid(Arr2) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Compare(%s): Invalid array #2.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
// first compare items at common indices
For i := 0 to Pred(Min(Arr1.Count,Arr2.Count)) do
  begin
    Result := CDA_ItemCompare(Arr1.Arr[i],Arr2.Arr[i]{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF});
    If Result <> 0 then
      Exit;
  end;
// all items at common indices match, compare lengths
If Arr1.Count < Arr2.Count then
  Result := -1
else If Arr1.Count > Arr2.Count then
  Result := +1
else
  Result := 0;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Same) or Defined(CDA_FuncReintroduce_Same)}
Function _CDA_Same(const Arr1, Arr2: TCDAArrayType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean;{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
Function CDA_Same(const Arr1, Arr2: TCDAArrayType{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF}): Boolean;
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr1) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Same(%s): Invalid array #1.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If not CDA_Valid(Arr2) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Same(%s): Invalid array #2.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr1.Count = Arr2.Count then
  begin
    Result := True;
    For i := 0 to Pred(Arr1.Count) do
      If CDA_ItemCompare(Arr1.Arr[i],Arr2.Arr[i]{$IFDEF CDA_CaseSensitiveBaseType},CaseSensitive{$ENDIF}) <> 0 then
        begin
          Result := False;
          Break{For i};
        end;
  end
else Result := False;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------
   
{$IF Defined(CDA_FuncOverride_Reverse) or Defined(CDA_FuncReintroduce_Reverse)}
procedure _CDA_Reverse(var Arr: TCDAArrayType);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Reverse(var Arr: TCDAArrayType);
{$IFEND}
var
  i:    Integer;
  Temp: TCDABaseType;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Reverse(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr.Count > 1 then
  For i := 0 to Pred(Arr.Count shr 1) do
    begin
      Temp := Arr.Arr[i];
      Arr.Arr[i] := Arr.Arr[Pred(Arr.Count) - i];
      Arr.Arr[Pred(Arr.Count) - i] := Temp;
    end;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Sort) or Defined(CDA_FuncReintroduce_Sort)}
procedure _CDA_Sort(var Arr: TCDAArrayType; Reversed: Boolean = False{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF});{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Sort(var Arr: TCDAArrayType; Reversed: Boolean = False{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF});
{$IFEND}
var
  Sorter: TListQuickSorter;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Sort(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr.Count > 1 then
  begin
  {$IFDEF CDA_CaseSensitiveBaseType}
    If CaseSensitive then
      Arr.InternalInt := -1
    else
      Arr.InternalInt := 0;
  {$ENDIF}
    Sorter := TListQuickSorter.Create(@Arr,CDA_SortFunc_ItemCompare,CDA_SortFunc_ItemExchange);
    try
      Sorter.Reversed := Reversed;
      Sorter.Sort(0,Pred(Arr.Count));
    finally
      Sorter.Free;
    end;
  end;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SortStabilized) or Defined(CDA_FuncReintroduce_SortStabilized)}
procedure _CDA_SortStabilized(var Arr: TCDAArrayType; Reversed: Boolean = False{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF});{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_SortStabilized(var Arr: TCDAArrayType; Reversed: Boolean = False{$IFDEF CDA_CaseSensitiveBaseType}; CaseSensitive: Boolean = False{$ENDIF});
{$IFEND}
var
  i:      Integer;
  Sorter: TListQuickSorter;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_SortStabilized(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If Arr.Count > 1 then
  begin
    New(PCDAIndexArray(Arr.InternalPtr));
    try
      SetLength(PCDAIndexArray(Arr.InternalPtr)^,Arr.Count);
      For i := Low(PCDAIndexArray(Arr.InternalPtr)^) to High(PCDAIndexArray(Arr.InternalPtr)^) do
        PCDAIndexArray(Arr.InternalPtr)^[i] := i;
    {$IFDEF CDA_CaseSensitiveBaseType}
      If CaseSensitive then
        Arr.InternalInt := -1
      else
        Arr.InternalInt := 0;
    {$ENDIF}
      Sorter := TListQuickSorter.Create(@Arr,CDA_SortFunc_ItemCompareStabilized,CDA_SortFunc_ItemExchangeStabilized);
      try
        Sorter.Reversed := Reversed;
        Sorter.Sort(0,Pred(Arr.Count));
      finally
        Sorter.Free;
      end;
      SetLength(PCDAIndexArray(Arr.InternalPtr)^,0);
    finally
      Dispose(PCDAIndexArray(Arr.InternalPtr));
      Arr.InternalPtr := nil;      
    end;
  end;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_FillFrom) or Defined(CDA_FuncReintroduce_FillFrom)}
procedure _CDA_FillFrom(var Arr: TCDAArrayType; Index: Integer; SecureCopy: Boolean = False);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_FillFrom(var Arr: TCDAArrayType; Index: Integer; SecureCopy: Boolean = False);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_FillFrom(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
If (Index >= 0) and (Index < Arr.Count) then
  begin
    For i := 0 to Pred(Arr.Count) do
      If i <> Index then
        begin
          CDA_ItemFinal(Arr.Arr[i]);
          Arr.Arr[i] := Arr.Arr[Index];
          If SecureCopy then
            CDA_ItemUnique(Arr.Arr[i]);
        end;
  end
else raise ECDAIndexOutOfBounds.CreateFmt('%sCDA_FillFrom(%s): Index (%d) out of bounds.',
             [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME,Index]);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_Fill) or Defined(CDA_FuncReintroduce_Fill)}
procedure _CDA_Fill(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_Fill(var Arr: TCDAArrayType;{$IFDEF CDA_ConstBaseType} const{$ENDIF} Item: TCDABaseType; SecureCopy: Boolean = False);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_Fill(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
For i := 0 to Pred(Arr.Count) do
  begin
    CDA_ItemFinal(Arr.Arr[i]);
    Arr.Arr[i] := Item;
    If SecureCopy then
      CDA_ItemUnique(Arr.Arr[i]);
  end;
end;
{$UNDEF CDA_FuncNamePrefix}

//==============================================================================

{$IF Defined(CDA_FuncOverride_WriteToStream) or Defined(CDA_FuncReintroduce_WriteToStream)}
procedure _CDA_WriteToStream(const Arr: TCDAArrayType; Stream: TStream);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_WriteToStream(const Arr: TCDAArrayType; Stream: TStream);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_WriteToStream(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
For i := 0 to Pred(Arr.Count) do
  CDA_ItemWrite(Arr.Arr[i],Stream);
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SaveToStream) or Defined(CDA_FuncReintroduce_SaveToStream)}
procedure _CDA_SaveToStream(const Arr: TCDAArrayType; Stream: TStream);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_SaveToStream(const Arr: TCDAArrayType; Stream: TStream);
{$IFEND}
var
  i:  Integer;
begin
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_SaveToStream(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
Stream_WriteInt32(Stream,Arr.Count);
For i := 0 to Pred(Arr.Count) do
  CDA_ItemWrite(Arr.Arr[i],Stream);
Stream_WriteUInt64(Stream,UInt64(Arr.UserData));
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_ReadFromStream) or Defined(CDA_FuncReintroduce_ReadFromStream)}
procedure _CDA_ReadFromStream(var Arr: TCDAArrayType; Stream: TStream);{$DEFINE CDA_FuncNamePrefix}
{$ELSE}
procedure CDA_ReadFromStream(var Arr: TCDAArrayType; Stream: TStream);
{$IFEND}
var
  i:  Integer;
begin
{
  Since we will be reading count-number of items into an array that is expected
  to be preallocated, it must already be valid/initialized.
}
If not CDA_Valid(Arr) then
  raise ECDAInvalidArray.CreateFmt('%sCDA_ReadFromStream(%s): Invalid array.',
          [{$IFDEF CDA_FuncNamePrefix}'_'{$ELSE}''{$ENDIF},CDA_ARRAY_NAME]);
For i := 0 to Pred(Arr.Count) do
  begin
    CDA_ItemFinal(Arr.Arr[i]);
    Arr.Arr[i] := CDA_ItemRead(Stream);
  end;
end;
{$UNDEF CDA_FuncNamePrefix}

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_LoadFromStream) or Defined(CDA_FuncReintroduce_LoadFromStream)}
procedure _CDA_LoadFromStream(var Arr: TCDAArrayType; Stream: TStream);
{$ELSE}
procedure CDA_LoadFromStream(var Arr: TCDAArrayType; Stream: TStream);
{$IFEND}
var
  i:  Integer;
begin
{
  If array was already initialized and therefore might contain some data, then
  we need to finalize them because they will be deleted or overwritten. Setting
  count to zero will do this for us.
}
If CDA_Validate(Arr) then
  CDA_SetCount(Arr,0);
CDA_SetCount(Arr,Stream_GetInt32(Stream));
For i := 0 to Pred(Arr.Count) do
  // all items are fresh, so there is no need to finalize them
  Arr.Arr[i] := CDA_ItemRead(Stream);
Arr.UserData := PtrInt(Stream_GetUInt64(Stream));
end;

//==============================================================================

{$IF Defined(CDA_FuncOverride_WriteToFile) or Defined(CDA_FuncReintroduce_WriteToFile)}
procedure _CDA_WriteToFile(const Arr: TCDAArrayType; const FileName: String);
{$ELSE}
procedure CDA_WriteToFile(const Arr: TCDAArrayType; const FileName: String);
{$IFEND}
var
  FileStream: TFileSTream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmCreate or fmShareDenyWrite);
try
  FileStream.Seek(0,soBeginning);
  CDA_WriteToStream(Arr,FileStream);
finally
  FileStream.Free;
end;
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_SaveToFile) or Defined(CDA_FuncReintroduce_SaveToFile)}
procedure _CDA_SaveToFile(const Arr: TCDAArrayType; const FileName: String);
{$ELSE}
procedure CDA_SaveToFile(const Arr: TCDAArrayType; const FileName: String);
{$IFEND}
var
  FileStream: TFileSTream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmCreate or fmShareDenyWrite);
try
  FileStream.Seek(0,soBeginning);
  CDA_SaveToStream(Arr,FileStream);
finally
  FileStream.Free;
end;
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_ReadFromFile) or Defined(CDA_FuncReintroduce_ReadFromFile)}
procedure _CDA_ReadFromFile(var Arr: TCDAArrayType; const FileName: String);
{$ELSE}
procedure CDA_ReadFromFile(var Arr: TCDAArrayType; const FileName: String);
{$IFEND}
var
  FileStream: TFileSTream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmOpenRead or fmShareDenyWrite);
try
  FileStream.Seek(0,soBeginning);
  CDA_ReadFromStream(Arr,FileStream);
finally
  FileStream.Free;
end;
end;

//------------------------------------------------------------------------------

{$IF Defined(CDA_FuncOverride_LoadFromFile) or Defined(CDA_FuncReintroduce_LoadFromFile)}
procedure _CDA_LoadFromFile(var Arr: TCDAArrayType; const FileName: String);
{$ELSE}
procedure CDA_LoadFromFile(var Arr: TCDAArrayType; const FileName: String);
{$IFEND}
var
  FileStream: TFileSTream;
begin
FileStream := TFileStream.Create(StrToRTL(FileName),fmOpenRead or fmShareDenyWrite);
try
  FileStream.Seek(0,soBeginning);
  CDA_LoadFromStream(Arr,FileStream);
finally
  FileStream.Free;
end;
end;

{$ENDIF}
