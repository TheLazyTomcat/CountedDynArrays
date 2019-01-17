{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Main implementation template

  ©František Milt 2019-01-17

  Version 1.0.2

  Dependencies:
    AuxTypes    - github.com/ncs-sniper/Lib.AuxTypes
    ListSorters - github.com/ncs-sniper/Lib.ListSorters

===============================================================================}
{$IFDEF CDA_Interface}

{$IFNDEF CDA_DisableFunc_Valid}       Function CDA_Valid(const Arr: TCDAArrayType): Boolean;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_Validate}    procedure CDA_Validate(var Arr: TCDAArrayType);{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_Init}        procedure CDA_Init(out Arr: TCDAArrayType); overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_Length}      Function CDA_Length(const Arr: TCDAArrayType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Capacity}    Function CDA_Capacity(const Arr: TCDAArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_FreeCapacity}Function CDA_FreeCapacity(const Arr: TCDAArrayType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Count}       Function CDA_Count(const Arr: TCDAArrayType): Integer; overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_Low}         Function CDA_Low(const Arr: TCDAArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_High}        Function CDA_High(const Arr: TCDAArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_CheckIndex}  Function CDA_CheckIndex(const Arr: TCDAArrayType; Index: Integer): Boolean; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_SetLength}   procedure CDA_SetLength(var Arr: TCDAArrayType; NewLength: Integer); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_SetCapacity} procedure CDA_SetCapacity(var Arr: TCDAArrayType; NewCapacity: Integer); overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_Grow}        Function CDA_Grow(var Arr: TCDAArrayType; GrowMode: TCDAGrowMode = agmFast; GrowFactor: Single = 1.0; DeltaMin: Integer = 1): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Shrink}      procedure CDA_Shrink(var Arr: TCDAArrayType; ShrinkMode: TCDAShrinkMode = asmNormal); overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_UniqueArray} procedure CDA_UniqueArray(var Arr: TCDAArrayType); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_CopyP}       Function CDA_Copy(const Src: TCDAArrayType; Index, Count: Integer): TCDAArrayType; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Copy}        Function CDA_Copy(const Src: TCDAArrayType): TCDAArrayType; overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_GetData}     Function CDA_GetData(const Arr: TCDAArrayType): PtrInt; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_SetData}     procedure CDA_SetData(var Arr: TCDAArrayType; Data: PtrInt); overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_GetItem}     Function CDA_GetItem(const Arr: TCDAArrayType; Index: Integer): TCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_GetItemPtr}  Function CDA_GetItemPtr(const Arr: TCDAArrayType; Index: Integer): PCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_SetItem}     procedure CDA_SetItem(var Arr: TCDAArrayType; Index: Integer; const Item: TCDABaseType); overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_First}       Function CDA_First(const Arr: TCDAArrayType): TCDABaseType; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Last}        Function CDA_Last(const Arr: TCDAArrayType): TCDABaseType; overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_IndexOf}     Function CDA_IndexOf(const Arr: TCDAArrayType; const Item: TCDABaseType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Add}         Function CDA_Add(var Arr: TCDAArrayType; const Item: TCDABaseType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Insert}      procedure CDA_Insert(var Arr: TCDAArrayType; Index: Integer; const Item: TCDABaseType); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Exchange}    procedure CDA_Exchange(var Arr: TCDAArrayType; Idx1, Idx2: Integer); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Move}        procedure CDA_Move(var Arr: TCDAArrayType; SrcIdx, DstIdx: Integer); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Remove}      Function CDA_Remove(var Arr: TCDAArrayType; const Item: TCDABaseType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Delete}      procedure CDA_Delete(var Arr: TCDAArrayType; Index: Integer); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Clear}       procedure CDA_Clear(var Arr: TCDAArrayType); overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_Same}        Function CDA_Same(const Arr1, Arr2: TCDAArrayType): Boolean; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Reverse}     procedure CDA_Reverse(var Arr: TCDAArrayType); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Sort}        procedure CDA_Sort(var Arr: TCDAArrayType; Reversed: Boolean = False); overload;{$ENDIF}

{$ENDIF}

//==============================================================================

{$IFDEF CDA_Implementation}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_ItemCompareSortFunc}
Function CDA_ItemCompareSortFunc(Context: Pointer; Idx1,Idx2: Integer): Integer;{$IFDEF CanInline} inline; {$ENDIF}
begin
Result := CDA_CompareFunc(TCDAArrayType(Context^).Arr[Idx1],TCDAArrayType(Context^).Arr[Idx2]);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_ItemExchangeSortFunc}
procedure CDA_ItemExchangeSortFunc(Context: Pointer; Idx1,Idx2: Integer);{$IFDEF CanInline} inline; {$ENDIF}
begin
CDA_Exchange(TCDAArrayType(Context^),Idx1,Idx2);
end;

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_ItemFinal}
{$IFDEF FPCDWM}{$PUSH}W5024{$ENDIF}
procedure CDA_ItemFinal(var Item: TCDABaseType); {$IFDEF CanInline} inline; {$ENDIF}
begin
end;
{$IFDEF FPCDWM}{$POP}{$ENDIF}
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_ItemUnique}
{$IFDEF FPCDWM}{$PUSH}W5024{$ENDIF}
procedure CDA_ItemUnique(var Item: TCDABaseType); {$IFDEF CanInline} inline; {$ENDIF}
begin
end;
{$IFDEF FPCDWM}{$POP}{$ENDIF}
{$ENDIF}

{$ENDIF}

//==============================================================================

{$IFNDEF CDA_DisableFunc_Valid}
Function CDA_Valid(const Arr: TCDAArrayType): Boolean;
begin
Result := (Arr.SigA = CDA_SIGA) and (Arr.SigB = CDA_SIGB) and (Arr.Count <= Length(Arr.Arr));
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Validate}
procedure CDA_Validate(var Arr: TCDAArrayType);
begin
If not CDA_Valid(Arr) then
  CDA_Init(Arr);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Init}
procedure CDA_Init(out Arr: TCDAArrayType);
begin
SetLength(Arr.Arr,0);
Arr.SigA := CDA_SIGA;
Arr.Count := 0;
Arr.Data := 0;
Arr.SigB := CDA_SIGB;
end;
{$ENDIF}

//==============================================================================

{$IFNDEF CDA_DisableFunc_Length}
Function CDA_Length(const Arr: TCDAArrayType): Integer;
begin
If CDA_Valid(Arr) then
  Result := Length(Arr.Arr)
else
  Result := 0;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Capacity}
Function CDA_Capacity(const Arr: TCDAArrayType): Integer;
begin
Result := CDA_Length(Arr);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_FreeCapacity}
Function CDA_FreeCapacity(const Arr: TCDAArrayType): Integer;
begin
If CDA_Valid(Arr) then
  Result := Length(Arr.Arr) - Arr.Count
else
  Result := 0;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Count}
Function CDA_Count(const Arr: TCDAArrayType): Integer;
begin
If CDA_Valid(Arr) then
  Result := Arr.Count
else
  Result := 0;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Low}
Function CDA_Low(const Arr: TCDAArrayType): Integer;
begin
// no need to check validity, this will always return 0
Result := Low(Arr.Arr);
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_High}
Function CDA_High(const Arr: TCDAArrayType): Integer;
begin
// CDA_Count checks for validity
Result := Pred(CDA_Count(Arr));
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_CheckIndex}
Function CDA_CheckIndex(const Arr: TCDAArrayType; Index: Integer): Boolean;
begin
// CDA_High checks for validity
Result := (Index >= CDA_Low(Arr)) and (Index <= CDA_High(Arr));
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_SetLength}
procedure CDA_SetLength(var Arr: TCDAArrayType; NewLength: Integer);
var
  i:  Integer;
begin
CDA_Validate(Arr);
If NewLength >= 0 then
  begin
    If NewLength < CDA_Count(Arr) then
      For i := NewLength to CDA_High(Arr) do
        CDA_ItemFinal(Arr.Arr[i]);
    SetLength(Arr.Arr,NewLength);
    If NewLength < CDA_Count(Arr) then
      Arr.Count := NewLength;
  end
else raise ERangeError.CreateFmt('CDA_SetLength: New length (%d) out of range.',[NewLength]);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_SetCapacity}
procedure CDA_SetCapacity(var Arr: TCDAArrayType; NewCapacity: Integer);
begin
CDA_SetLength(Arr,NewCapaCity);
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_Grow}
Function CDA_Grow(var Arr: TCDAArrayType; GrowMode: TCDAGrowMode = agmFast; GrowFactor: Single = 1.0; DeltaMin: Integer = 1): Integer;
begin
CDA_Validate(Arr);
If DeltaMin < 1 then
  DeltaMin := 1;
If (CDA_Count(Arr) + DeltaMin) > CDA_Capacity(Arr) then
  begin
    If (CDA_Capacity(Arr) > 0) or (GrowMode = agmSlow) then
      case GrowMode of
        agmLinear:
          Result := Trunc(GrowFactor);
        agmFast:
          Result := Trunc(CDA_Capacity(Arr) * GrowFactor);
        agmFastAttenuated:
          If CDA_Capacity(Arr) >= CDA_GROW_ATTENUATE_THRESHOLD then
            Result := Trunc(CDA_GROW_ATTENUATE_THRESHOLD / 16)
          else
            Result := Trunc(CDA_Capacity(Arr) * GrowFactor);
      else
       {agmSlow}
        Result := 1;
      end
    else Result := CDA_INITIAL_CAPACITY;
    If Result < DeltaMin then
      Result := DeltaMin;
    If Result < 1 then
      Result := 1;
    // do the growing
    CDA_SetCapacity(Arr,CDA_Capacity(Arr) + Result);
  end
else Result := 0;
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_Shrink}
procedure CDA_Shrink(var Arr: TCDAArrayType; ShrinkMode: TCDAShrinkMode = asmNormal);
begin
CDA_Validate(Arr);
If CDA_Capacity(Arr) > 0 then
  case ShrinkMode of
    asmNormal:  If CDA_Capacity(Arr) > CDA_INITIAL_CAPACITY then
                  begin
                    If CDA_Count(Arr) < (CDA_Capacity(Arr) div 4) then
                      CDA_SetCapacity(Arr,CDA_Capacity(Arr) div 4)
                  end
                else
                  begin
                    If CDA_Count(Arr) <= 0 then
                      CDA_SetCapacity(Arr,0);
                  end;
    asmToCount: CDA_SetCapacity(Arr,CDA_Count(Arr));
  else
   {asmKeepCap}
    // do nothing
  end;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_UniqueArray}
procedure CDA_UniqueArray(var Arr: TCDAArrayType);
var
  i:  Integer;
begin
// CDA_SetLength validates the array
CDA_SetLength(Arr,CDA_Capacity(Arr));
For i := CDA_Low(Arr) to CDA_High(Arr) do
  CDA_ItemUnique(Arr.Arr[i]);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_CopyP}
{$IFDEF FPCDWM}{$PUSH}W5093 W5094 W5060{$ENDIF}
Function CDA_Copy(const Src: TCDAArrayType; Index, Count: Integer): TCDAArrayType;
var
  i:  Integer;
begin
CDA_Validate(Result);
// CDA_CheckIndex checks for validity of the source array
If CDA_CheckIndex(Src,Index) then
  begin
    If (Index + Count) > CDA_Count(Src) then
      Count := CDA_Count(Src) - Index;
    Result.Arr := Copy(Src.Arr,Index,Count);
    For i := CDA_Low(Result) to CDA_High(Result) do
      CDA_ItemUnique(Result.Arr[i]);
    Result.SigA := CDA_SIGA;
    Result.Count := Count;
    Result.Data := Src.Data;
    Result.SigB := CDA_SIGB;
  end;
end;
{$IFDEF FPCDWM}{$POP}{$ENDIF}
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Copy}
{$IFDEF FPCDWM}{$PUSH}W5093 W5094 W5060{$ENDIF}
Function CDA_Copy(const Src: TCDAArrayType): TCDAArrayType;
var
  i:  Integer;
begin
CDA_Validate(Result);
If CDA_Valid(Src) then
  begin
    Result.Arr := Copy(Src.Arr);
    For i := CDA_Low(Result) to CDA_High(Result) do
      CDA_ItemUnique(Result.Arr[i]);    
    Result.SigA := CDA_SIGA;
    Result.Count := Src.Count;
    Result.Data := Src.Data;
    Result.SigB := CDA_SIGB;
  end;
end;
{$IFDEF FPCDWM}{$POP}{$ENDIF}
{$ENDIF}

//------------------------------------------------------------------------------
  
{$IFNDEF CDA_DisableFunc_GetData}
Function CDA_GetData(const Arr: TCDAArrayType): PtrInt;
begin
If CDA_Valid(Arr) then
  Result := Arr.Data
else
  Result := 0;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_SetData}
procedure CDA_SetData(var Arr: TCDAArrayType; Data: PtrInt);
begin
CDA_Validate(Arr);
Arr.Data := Data;
end;
{$ENDIF}

//------------------------------------------------------------------------------
   
{$IFNDEF CDA_DisableFunc_GetItem}
Function CDA_GetItem(const Arr: TCDAArrayType; Index: Integer): TCDABaseType;
begin
// CDA_CheckIndex checks for validity, exception is raised for invalid array
If CDA_CheckIndex(Arr,Index) then
  Result := Arr.Arr[Index]
else
  raise Exception.CreateFmt('CDA_GetItem: Index (%d) out of bounds.',[Index]);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_GetItemPtr}
Function CDA_GetItemPtr(const Arr: TCDAArrayType; Index: Integer): PCDABaseType;
begin
// CDA_CheckIndex checks for validity, exception is raised for invalid array
If CDA_CheckIndex(Arr,Index) then
  Result := Addr(Arr.Arr[Index])
else
  raise Exception.CreateFmt('CDA_GetItemPtr: Index (%d) out of bounds.',[Index]);
end;
{$ENDIF}

//------------------------------------------------------------------------------
  
{$IFNDEF CDA_DisableFunc_SetItem}
procedure CDA_SetItem(var Arr: TCDAArrayType; Index: Integer; const Item: TCDABaseType);
begin
// CDA_CheckIndex checks for validity, exception is raised for invalid array
If CDA_CheckIndex(Arr,Index) then
  Arr.Arr[Index] := Item
else
  raise Exception.CreateFmt('CDA_SetItem: Index (%d) out of bounds.',[Index]);
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_First}
Function CDA_First(const Arr: TCDAArrayType): TCDABaseType;
begin
// CDA_Count checks for validity, exception is raised for invalid array
If CDA_Count(Arr) > 0 then
  Result := Arr.Arr[CDA_Low(Arr)]
else
  raise Exception.Create('CDA_First: Array is empty.');
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_Last}
Function CDA_Last(const Arr: TCDAArrayType): TCDABaseType;
begin
// CDA_Count checks for validity, exception is raised for invalid array
If CDA_Count(Arr) > 0 then
  Result := Arr.Arr[CDA_High(Arr)]
else
  raise Exception.Create('CDA_Last: Array is empty.');
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_IndexOf}
Function CDA_IndexOf(const Arr: TCDAArrayType; const Item: TCDABaseType): Integer;
var
  i:  Integer;
begin
Result := -1;
// CDA_High checks for validity, -1 is returned for invalid array
For i := CDA_Low(Arr) to CDA_High(Arr) do
  If CDA_CompareFunc(Arr.Arr[i],Item) = 0 then
    begin
      Result := i;
      Break{For i};
    end;
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_Add}
Function CDA_Add(var Arr: TCDAArrayType; const Item: TCDABaseType): Integer;
begin
CDA_Validate(Arr);
CDA_Grow(Arr);
Result := CDA_Count(Arr);
Arr.Arr[Result] := Item;
Inc(Arr.Count);
end;
{$ENDIF}

//------------------------------------------------------------------------------
   
{$IFNDEF CDA_DisableFunc_Insert}
procedure CDA_Insert(var Arr: TCDAArrayType; Index: Integer; const Item: TCDABaseType);
var
  i:  Integer;
begin
CDA_Validate(Arr);
If CDA_CheckIndex(Arr,Index) then
  begin
    CDA_Grow(Arr);
    For i := CDA_High(Arr) downto Index do
      Arr.Arr[i + 1] := Arr.Arr[i];
    Arr.Arr[Index] := Item;
    Inc(Arr.Count);
  end
else CDA_Add(Arr,Item);
end;
{$ENDIF}

//------------------------------------------------------------------------------
   
{$IFNDEF CDA_DisableFunc_Exchange}
procedure CDA_Exchange(var Arr: TCDAArrayType; Idx1, Idx2: Integer);
var
  Temp: TCDABaseType;
begin
CDA_Validate(Arr);
If Idx1 <> Idx2 then
  begin
    If not CDA_CheckIndex(Arr,Idx1) then
      raise Exception.CreateFmt('CDA_Exchange: First index (%d) out of bounds.',[Idx1]);
    If not CDA_CheckIndex(Arr,Idx2) then
      raise Exception.CreateFmt('CDA_Exchange: Second index (%d) out of bounds.',[Idx2]);
    Temp := Arr.Arr[Idx1];
    Arr.Arr[Idx1] := Arr.Arr[Idx2];
    Arr.Arr[Idx2] := Temp;
  end;
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_Move}
procedure CDA_Move(var Arr: TCDAArrayType; SrcIdx, DstIdx: Integer);
var
  Temp: TCDABaseType;
  i:    Integer;
begin
CDA_Validate(Arr);
If SrcIdx <> DstIdx then
  begin
    If not CDA_CheckIndex(Arr,SrcIdx) then
      raise Exception.CreateFmt('CDA_Move: Source index (%d) out of bounds.',[SrcIdx]);
    If not CDA_CheckIndex(Arr,DstIdx) then
      raise Exception.CreateFmt('CDA_Move: Destination index (%d) out of bounds.',[DstIdx]);
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
{$ENDIF}

//------------------------------------------------------------------------------
     
{$IFNDEF CDA_DisableFunc_Remove}
Function CDA_Remove(var Arr: TCDAArrayType; const Item: TCDABaseType): Integer;
begin
CDA_Validate(Arr);
Result := CDA_IndexOf(Arr,Item);
If CDA_CheckIndex(Arr,Result) then
  CDA_Delete(Arr,Result);
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_Delete}
procedure CDA_Delete(var Arr: TCDAArrayType; Index: Integer);
var
  i:  Integer;
begin
CDA_Validate(Arr);
If CDA_CheckIndex(Arr,Index) then
  begin
    CDA_ItemFinal(Arr.Arr[Index]);
    For i := Index to Pred(CDA_High(Arr)) do
      Arr.Arr[i] := Arr.Arr[i + 1];
    Dec(Arr.Count);
    CDA_Shrink(Arr);
  end
else raise Exception.CreateFmt('CDA_Delete: Index (%d) out of bounds.',[Index]);
end;
{$ENDIF}

//------------------------------------------------------------------------------
       
{$IFNDEF CDA_DisableFunc_Clear}
procedure CDA_Clear(var Arr: TCDAArrayType);
begin
CDA_SetLength(Arr,0);
end;
{$ENDIF}

//------------------------------------------------------------------------------
      
{$IFNDEF CDA_DisableFunc_Same}
Function CDA_Same(const Arr1, Arr2: TCDAArrayType): Boolean;
var
  i:  Integer;
begin
If CDA_Valid(Arr1) and CDA_Valid(Arr2) and (CDA_Count(Arr1) = CDA_Count(Arr2)) then
  begin
    Result := True;
    For i := CDA_Low(Arr1) to CDA_High(Arr1) do
      If CDA_CompareFunc(Arr1.Arr[i],Arr2.Arr[i]) <> 0 then
        begin
          Result := False;
          Break{For i};
        end;
  end
else Result := False;
end;
{$ENDIF}

//------------------------------------------------------------------------------
   
{$IFNDEF CDA_DisableFunc_Reverse}
procedure CDA_Reverse(var Arr: TCDAArrayType);
var
  i:    Integer;
  Temp: TCDABaseType;
begin
CDA_Validate(Arr);
If CDA_Count(Arr) > 1 then
  For i := CDA_Low(Arr) to Pred(CDA_Count(Arr) shr 1) do
    begin
      Temp := Arr.Arr[i];
      Arr.Arr[i] := Arr.Arr[CDA_High(Arr) - i];
      Arr.Arr[CDA_High(Arr) - i] := Temp;
    end;
end;
{$ENDIF}

//------------------------------------------------------------------------------
  
{$IFNDEF CDA_DisableFunc_Sort}
procedure CDA_Sort(var Arr: TCDAArrayType; Reversed: Boolean = False);
var
  Sorter: TListQuickSorter;
begin
CDA_Validate(Arr);
If CDA_Count(Arr) > 1 then
  begin
    Sorter := TListQuickSorter.Create(@Arr,CDA_ItemCompareSortFunc,CDA_ItemExchangeSortFunc);
    try
      Sorter.Reversed := Reversed;
      Sorter.Sort(CDA_Low(Arr),CDA_High(Arr));
    finally
      Sorter.Free;
    end;
  end;
end;
{$ENDIF}

{$ENDIF}
