{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Main implementation template

  ©František Milt 2018-12-08

  Version 1.0

  Dependencies:
    AuxTypes    - github.com/ncs-sniper/Lib.AuxTypes
    ListSorters - github.com/ncs-sniper/Lib.ListSorters

===============================================================================}
{$IFDEF CDA_Interface}

{$IFNDEF CDA_DisableFunc_Length}      Function Length(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_Capacity}    Function Capacity(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_FreeCapacity}Function FreeCapacity(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_Count}       Function Count(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_Low}         Function Low(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_High}        Function High(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_CheckIndex}  Function CheckIndex(const Arr: TArrayType; Index: Integer): Boolean; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_Init}        procedure Init(out Arr: TArrayType); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_SetLength}   procedure SetLength(var Arr: TArrayType; NewLength: Integer); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_SetCapacity} procedure SetCapacity(var Arr: TArrayType; NewCapacity: Integer); overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_Grow}        Function Grow(var Arr: TArrayType; GrowMode: TCDAGrowMode = agmFast; GrowFactor: Single = 1.0; DeltaMin: Integer = 1): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Shrink}      procedure Shrink(var Arr: TArrayType; ShrinkMode: TCDAShrinkMode = asmNormal); overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_UniqueArray} procedure UniqueArray(var Arr: TArrayType); overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_CopyP}       Function Copy(const Src: TArrayType; Index, Count: Integer): TArrayType; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Copy}        Function Copy(const Src: TArrayType): TArrayType; overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_GetData}     Function GetData(const Arr: TArrayType): PtrInt; overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}
{$IFNDEF CDA_DisableFunc_SetData}     procedure SetData(var Arr: TArrayType; Data: PtrInt); overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_GetItem}     Function GetItem(const Arr: TArrayType; Index: Integer): TBaseType; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_SetItem}     procedure SetItem(var Arr: TArrayType; Index: Integer; const Item: TBaseType); overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_First}       Function First(const Arr: TArrayType): TBaseType; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Last}        Function Last(const Arr: TArrayType): TBaseType; overload;{$ENDIF}

{$IFNDEF CDA_DisableFunc_IndexOf}     Function IndexOf(const Arr: TArrayType; const Item: TBaseType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Add}         Function Add(var Arr: TArrayType; const Item: TBaseType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Insert}      procedure Insert(var Arr: TArrayType; Index: Integer; const Item: TBaseType); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Exchange}    procedure Exchange(var Arr: TArrayType; Idx1, Idx2: Integer); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Move}        procedure Move(var Arr: TArrayType; SrcIdx, DstIdx: Integer); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Remove}      Function Remove(var Arr: TArrayType; const Item: TBaseType): Integer; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Delete}      procedure Delete(var Arr: TArrayType; Index: Integer); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Clear}       procedure Clear(var Arr: TArrayType); overload;{$IFDEF CanInline} inline; {$ENDIF}{$ENDIF}

{$IFNDEF CDA_DisableFunc_Same}        Function Same(const Arr1, Arr2: TArrayType): Boolean; overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Reverse}     procedure Reverse(var Arr: TArrayType); overload;{$ENDIF}
{$IFNDEF CDA_DisableFunc_Sort}        procedure Sort(var Arr: TArrayType; Reversed: Boolean = False); overload;{$ENDIF}

{$ENDIF}

//==============================================================================

{$IFDEF CDA_Implementation}

{$IFNDEF CDA_DisableFunc_ItemCompareFunc}
Function CDA_ItemCompareFunc(Context: Pointer; Idx1,Idx2: Integer): Integer;
begin
Result := CDA_CompareFunc(TArrayType(Context^).Arr[Idx1],TArrayType(Context^).Arr[Idx2]);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_ItemExchangeFunc}
procedure CDA_ItemExchangeFunc(Context: Pointer; Idx1,Idx2: Integer);
begin
Exchange(TArrayType(Context^),Idx1,Idx2);
end;
{$ENDIF}

//==============================================================================

{$IFNDEF CDA_DisableFunc_Length}
Function Length(const Arr: TArrayType): Integer;
begin
Result := System.Length(Arr.Arr);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Capacity}
Function Capacity(const Arr: TArrayType): Integer;
begin
Result := System.Length(Arr.Arr);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_FreeCapacity}
Function FreeCapacity(const Arr: TArrayType): Integer;
begin
Result := System.Length(Arr.Arr) - Arr.Count;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Count}
Function Count(const Arr: TArrayType): Integer;
begin
Result := Arr.Count;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Low}
Function Low(const Arr: TArrayType): Integer;
begin
Result := System.Low(Arr.Arr);
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_High}
Function High(const Arr: TArrayType): Integer;
begin
Result := Pred(Arr.Count);
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_CheckIndex}
Function CheckIndex(const Arr: TArrayType; Index: Integer): Boolean;
begin
Result := (Index >= System.Low(Arr.Arr)) and (Index < Arr.Count);
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_Init}
procedure Init(out Arr: TArrayType);
begin
System.SetLength(Arr.Arr,0);
Arr.Count := 0;
Arr.Data := 0;
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_SetLength}
procedure SetLength(var Arr: TArrayType; NewLength: Integer);
begin
If NewLength >= 0 then
  begin
    System.SetLength(Arr.Arr,NewLength);
    If Arr.Count > NewLength then
      Arr.Count := NewLength;
  end
else raise ERangeError.CreateFmt('SetLength: New length (%d) out of range.',[NewLength]);
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_SetCapacity}
procedure SetCapacity(var Arr: TArrayType; NewCapacity: Integer);
begin
SetLength(Arr,NewCapaCity);
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_Grow}
Function Grow(var Arr: TArrayType; GrowMode: TCDAGrowMode = agmFast; GrowFactor: Single = 1.0; DeltaMin: Integer = 1): Integer;
begin
If DeltaMin < 1 then
  DeltaMin := 1;
If (Count(Arr) + DeltaMin) > Capacity(Arr) then
  begin
    If (Capacity(Arr) > 0) or (GrowMode = agmSlow) then
      case GrowMode of
        agmLinear:
          Result := Trunc(GrowFactor);
        agmFast:
          Result := Trunc(Capacity(Arr) * GrowFactor);
        agmFastAttenuated:
          If Capacity(Arr) >= DYNARRAY_GROW_ATTENUATE_THRESHOLD then
            Result := Trunc(DYNARRAY_GROW_ATTENUATE_THRESHOLD / 16)
          else
            Result := Trunc(Capacity(Arr) * GrowFactor);
      else
       {agmSlow}
        Result := 1;
      end
    else Result := DYNARRAY_INITIAL_CAPACITY;
    If Result < DeltaMin then
      Result := DeltaMin;
    If Result < 1 then
      Result := 1;
    // do the growing
    SetCapacity(Arr,Capacity(Arr) + Result);
  end
else Result := 0;
end;
{$ENDIF}

//------------------------------------------------------------------------------
 
{$IFNDEF CDA_DisableFunc_Shrink}
procedure Shrink(var Arr: TArrayType; ShrinkMode: TCDAShrinkMode = asmNormal);
begin
If Capacity(Arr) > 0 then
  case ShrinkMode of
    asmNormal:  If Capacity(Arr) > DYNARRAY_INITIAL_CAPACITY then
                  begin
                    If Count(Arr) < (Capacity(Arr) div 4) then
                      SetCapacity(Arr,Capacity(Arr) div 4)
                  end
                else
                  begin
                    If Count(Arr) <= 0 then
                      SetCapacity(Arr,0);
                  end;
    asmToCount: SetCapacity(Arr,Count(Arr));
  else
   {asmKeepCap}
    // do nothing
  end;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_UniqueArray}
procedure UniqueArray(var Arr: TArrayType);
begin
SetLength(Arr,Capacity(Arr));
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_CopyP}
Function Copy(const Src: TArrayType; Index, Count: Integer): TArrayType;
begin
Init(Result);
If CheckIndex(Src,Index) then
  begin
    // note - count function cannot be used here because of collision with parameter
    If (Index + Count) > Src.Count then
      Count := Src.Count - Index;
    Result.Arr := System.Copy(Src.Arr,Index,Count);
    Result.Count := Count;
    Result.Data := Src.Data;
  end;
end;
{$ENDIF}

//------------------------------------------------------------------------------

{$IFNDEF CDA_DisableFunc_Copy}
Function Copy(const Src: TArrayType): TArrayType;
begin
Init(Result);
Result.Arr := System.Copy(Src.Arr);
Result.Count := Src.Count;
Result.Data := Src.Data;
end;
{$ENDIF}

//------------------------------------------------------------------------------
  
{$IFNDEF CDA_DisableFunc_GetData}
Function GetData(const Arr: TArrayType): PtrInt;
begin
Result := Arr.Data;
end;
{$ENDIF}

//------------------------------------------------------------------------------
   
{$IFNDEF CDA_DisableFunc_SetData}
procedure SetData(var Arr: TArrayType; Data: PtrInt);
begin
Arr.Data := Data;
end;
{$ENDIF}

//------------------------------------------------------------------------------
   
{$IFNDEF CDA_DisableFunc_GetItem}
Function GetItem(const Arr: TArrayType; Index: Integer): TBaseType;
begin
If CheckIndex(Arr,Index) then
  Result := Arr.Arr[Index]
else
  raise Exception.CreateFmt('GetItem: Index (%d) out of bounds.',[Index]);
end;
{$ENDIF}

//------------------------------------------------------------------------------
  
{$IFNDEF CDA_DisableFunc_SetItem}
procedure SetItem(var Arr: TArrayType; Index: Integer; const Item: TBaseType);
begin
If CheckIndex(Arr,Index) then
  Arr.Arr[Index] := Item
else
  raise Exception.CreateFmt('SetItem: Index (%d) out of bounds.',[Index]);
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_First}
Function First(const Arr: TArrayType): TBaseType;
begin
If Count(Arr) > 0 then
  Result := Arr.Arr[Low(Arr)]
else
  raise Exception.Create('First: Array is empty.');
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_Last}
Function Last(const Arr: TArrayType): TBaseType;
begin
If Count(Arr) > 0 then
  Result := Arr.Arr[High(Arr)]
else
  raise Exception.Create('Last: Array is empty.');
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_IndexOf}
Function IndexOf(const Arr: TArrayType; const Item: TBaseType): Integer;
var
  i:  Integer;
begin
Result := -1;
For i := Low(Arr) to High(Arr) do
  If CDA_CompareFunc(Arr.Arr[i],Item) = 0 then
    begin
      Result := i;
      Break{For i};
    end;
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_Add}
Function Add(var Arr: TArrayType; const Item: TBaseType): Integer;
begin
Grow(Arr);
Result := Count(Arr);
Arr.Arr[Result] := Item;
Inc(Arr.Count);
end;
{$ENDIF}

//------------------------------------------------------------------------------
   
{$IFNDEF CDA_DisableFunc_Insert}
procedure Insert(var Arr: TArrayType; Index: Integer; const Item: TBaseType);
var
  i:  Integer;
begin
If CheckIndex(Arr,Index) then
  begin
    Grow(Arr);
    For i := High(Arr) downto Index do
      Arr.Arr[i + 1] := Arr.Arr[i];
    Arr.Arr[Index] := Item;
    Inc(Arr.Count);
  end
else Add(Arr,Item);
end;
{$ENDIF}

//------------------------------------------------------------------------------
   
{$IFNDEF CDA_DisableFunc_Exchange}
procedure Exchange(var Arr: TArrayType; Idx1, Idx2: Integer);
var
  Temp: TBaseType;
begin
If Idx1 <> Idx2 then
  begin
    If not CheckIndex(Arr,Idx1) then
      raise Exception.CreateFmt('Exchange: First index (%d) out of bounds.',[Idx1]);
    If not CheckIndex(Arr,Idx2) then
      raise Exception.CreateFmt('Exchange: Second index (%d) out of bounds.',[Idx2]);
    Temp := Arr.Arr[Idx1];
    Arr.Arr[Idx1] := Arr.Arr[Idx2];
    Arr.Arr[Idx2] := Temp;
  end;
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_Move}
procedure Move(var Arr: TArrayType; SrcIdx, DstIdx: Integer);
var
  Temp: TBaseType;
  i:    Integer;
begin
If SrcIdx <> DstIdx then
  begin
    If not CheckIndex(Arr,SrcIdx) then
      raise Exception.CreateFmt('Move: Source index (%d) out of bounds.',[SrcIdx]);
    If not CheckIndex(Arr,DstIdx) then
      raise Exception.CreateFmt('Move: Destination index (%d) out of bounds.',[DstIdx]);
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
Function Remove(var Arr: TArrayType; const Item: TBaseType): Integer;
begin
Result := IndexOf(Arr,Item);
If CheckIndex(Arr,Result) then
  Delete(Arr,Result);
end;
{$ENDIF}

//------------------------------------------------------------------------------
    
{$IFNDEF CDA_DisableFunc_Delete}
procedure Delete(var Arr: TArrayType; Index: Integer);
var
  i:  Integer;
begin
If CheckIndex(Arr,Index) then
  begin
    For i := Index to Pred(High(Arr)) do
      Arr.Arr[i] := Arr.Arr[i + 1];
    Dec(Arr.Count);
    Shrink(Arr);
  end
else raise Exception.CreateFmt('Delete: Index (%d) out of bounds.',[Index]);
end;
{$ENDIF}

//------------------------------------------------------------------------------
       
{$IFNDEF CDA_DisableFunc_Clear}
procedure Clear(var Arr: TArrayType);
begin
SetLength(Arr,0);
end;
{$ENDIF}

//------------------------------------------------------------------------------
      
{$IFNDEF CDA_DisableFunc_Same}
Function Same(const Arr1, Arr2: TArrayType): Boolean;
var
  i:  Integer;
begin
If Count(Arr1) = Count(Arr2) then
  begin
    Result := True;
    For i := Low(Arr1) to High(Arr1) do
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
procedure Reverse(var Arr: TArrayType);
var
  i:    Integer;
  Temp: TBaseType;
begin
If Count(Arr) > 1 then
  For i := Low(Arr) to Pred(Count(Arr) shr 1) do
    begin
      Temp := Arr.Arr[i];
      Arr.Arr[i] := Arr.Arr[High(Arr) - i];
      Arr.Arr[High(Arr) - i] := Temp;
    end;
end;
{$ENDIF}

//------------------------------------------------------------------------------
  
{$IFNDEF CDA_DisableFunc_Sort}
procedure Sort(var Arr: TArrayType; Reversed: Boolean = False);
var
  Sorter: TListQuickSorter;
begin
If Count(Arr) > 1 then
  begin
    Sorter := TListQuickSorter.Create(@Arr,CDA_ItemCompareFunc,CDA_ItemExchangeFunc);
    try
      Sorter.Reversed := Reversed;
      Sorter.Sort(Low(Arr),High(Arr));
    finally
      Sorter.Free;
    end;
  end;
end;
{$ENDIF}

{$ENDIF}