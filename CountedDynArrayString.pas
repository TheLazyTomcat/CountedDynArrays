{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Counted dynamic array of String values

  ©František Milt 2018-12-08

  Version 1.0

  Dependencies:
    AuxTypes    - github.com/ncs-sniper/Lib.AuxTypes
    ListSorters - github.com/ncs-sniper/Lib.ListSorters

===============================================================================}
unit CountedDynArrayString;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TStringCountedDynArray = record
    Arr:    array of String;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PStringCountedDynArray = ^TStringCountedDynArray;

  TBaseType = String;
  TArrayType = TStringCountedDynArray;

{$DEFINE CDA_DisableFunc_ItemCompareFunc}
{$DEFINE CDA_DisableFunc_IndexOf}
{$DEFINE CDA_DisableFunc_Remove}
{$DEFINE CDA_DisableFunc_Same}
{$DEFINE CDA_DisableFunc_Sort}

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

// overriden functions
Function CDA_IndexOf(const Arr: TArrayType; const Item: TBaseType; CaseSensitive: Boolean = False): Integer; overload;
Function CDA_Remove(var Arr: TArrayType; const Item: TBaseType; CaseSensitive: Boolean = False): Integer; overload;
Function CDA_Same(const Arr1, Arr2: TArrayType; CaseSensitive: Boolean = False): Boolean; overload;
procedure CDA_Sort(var Arr: TArrayType; Reversed: Boolean = False; CaseSensitive: Boolean = False); overload;

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(const A,B: String; CaseSensitive: Boolean): Integer;
begin
If CaseSensitive then
  Result := -AnsiCompareStr(A,B)
else
  Result := -AnsiCompareText(A,B);
end;

//------------------------------------------------------------------------------

Function CDA_ItemCompareFuncCS(Context: Pointer; Idx1,Idx2: Integer): Integer;
begin
Result := CDA_CompareFunc(TArrayType(Context^).Arr[Idx1],TArrayType(Context^).Arr[Idx2],True);
end;

//------------------------------------------------------------------------------

Function CDA_ItemCompareFuncCI(Context: Pointer; Idx1,Idx2: Integer): Integer;
begin
Result := CDA_CompareFunc(TArrayType(Context^).Arr[Idx1],TArrayType(Context^).Arr[Idx2],True);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

//------------------------------------------------------------------------------

Function CDA_IndexOf(const Arr: TArrayType; const Item: TBaseType; CaseSensitive: Boolean = False): Integer;
var
  i:  Integer;
begin
Result := -1;
For i := CDA_Low(Arr) to CDA_High(Arr) do
  If CDA_CompareFunc(Arr.Arr[i],Item,CaseSensitive) = 0 then
    begin
      Result := i;
      Break{For i};
    end;
end;

//------------------------------------------------------------------------------

Function CDA_Remove(var Arr: TArrayType; const Item: TBaseType; CaseSensitive: Boolean = False): Integer;
begin
Result := CDA_IndexOf(Arr,Item,CaseSensitive);
If CDA_CheckIndex(Arr,Result) then
  CDA_Delete(Arr,Result);
end;

//------------------------------------------------------------------------------

Function CDA_Same(const Arr1, Arr2: TArrayType; CaseSensitive: Boolean = False): Boolean;
var
  i:  Integer;
begin
If CDA_Count(Arr1) = CDA_Count(Arr2) then
  begin
    Result := True;
    For i := CDA_Low(Arr1) to CDA_High(Arr1) do
      If CDA_CompareFunc(Arr1.Arr[i],Arr2.Arr[i],CaseSensitive) <> 0 then
        begin
          Result := False;
          Break{For i};
        end;
  end
else Result := False;
end;

//------------------------------------------------------------------------------

procedure CDA_Sort(var Arr: TArrayType; Reversed: Boolean = False; CaseSensitive: Boolean = False);
var
  Sorter: TListQuickSorter;
begin
If CaseSensitive then
  Sorter := TListQuickSorter.Create(@Arr,CDA_ItemCompareFuncCS,CDA_ItemExchangeFunc)
else
  Sorter := TListQuickSorter.Create(@Arr,CDA_ItemCompareFuncCI,CDA_ItemExchangeFunc);
try
  Sorter.Reversed := Reversed;
  Sorter.Sort(CDA_Low(Arr),CDA_High(Arr));
finally
  Sorter.Free;
end;
end;

end.
