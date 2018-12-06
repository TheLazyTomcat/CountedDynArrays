Function Length(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer;
begin
Result := System.Length(Arr.Arr);
end;

//------------------------------------------------------------------------------

Function Capacity(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer;
begin
Result := System.Length(Arr.Arr);
end;

//------------------------------------------------------------------------------

Function FreeCapacity(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer;
begin
Result := System.Length(Arr.Arr) - Arr.Count;
end;

//------------------------------------------------------------------------------

Function Count(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer;
begin
Result := Arr.Count;
end;

//------------------------------------------------------------------------------

Function Low(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer;
begin
Result := System.Low(Arr.Arr);
end;

//------------------------------------------------------------------------------

Function High(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): Integer;
begin
Result := Pred(Arr.Count);
end;

//------------------------------------------------------------------------------

Function CheckIndex(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; Index: Integer): Boolean;
begin
Result := (Index >= System.Low(Arr.Arr)) and (Index < Arr.Count);
end;

//------------------------------------------------------------------------------

procedure Init(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF});
begin
System.SetLength(Arr.Arr,0);
Arr.Count := 0;
Arr.Data := 0;
end;

//------------------------------------------------------------------------------

procedure SetLength(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; NewLength: Integer);
begin
If NewLength >= 0 then
  begin
    System.SetLength(Arr.Arr,NewLength);
    If Arr.Count > NewLength then
      Arr.Count := NewLength;
  end
else raise ERangeError.CreateFmt('SetLength: New length (%d) out of range.',[NewLength]);
end;

//------------------------------------------------------------------------------

procedure SetCapacity(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; NewCapacity: Integer);
begin
SetLength(Arr,NewCapaCity);
end;

//------------------------------------------------------------------------------

procedure Clear(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF});
begin
SetLength(Arr,0);
end;

//------------------------------------------------------------------------------

Function Grow(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; GrowMode: TArrayGrowMode = agmFast; GrowFactor: Single = 2.0; DeltaMin: Integer = 1): Integer;
begin
If DeltaMin < 1 then
  DeltaMin := 1;
If (Count(Arr) + DeltaMin) > Capacity(Arr) then
  begin
    If (Capacity(Arr) <= 0) and (GrowMode <> agmSlow) then
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

//------------------------------------------------------------------------------

procedure Shrink(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; ShrinkMode: TArrayShrinkMode = asmNormal);
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

//------------------------------------------------------------------------------

procedure UniqueArray(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF});
begin
SetLength(Arr,Capacity(Arr));
end;

//------------------------------------------------------------------------------

procedure Copy(const Src: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; out Dst: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF});
begin
Dst.Arr := System.Copy(Src.Arr);
Dst.Count := Src.Count;
Dst.Data := Src.Data;
end;

//------------------------------------------------------------------------------

Function Copy(const Src: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}): {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF};
begin
Copy(Src,Result);
end;

//------------------------------------------------------------------------------

Function GetItem(const Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; Index: Integer): {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_BaseTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_BaseType.Inc'}{$ENDIF};
begin
If CheckIndex(Arr,Index) then
  Result := Arr.Arr[Index]
else
  raise Exception.CreateFmt('GetItem: Index (%d) out of bounds.',[Index]);
end;

//------------------------------------------------------------------------------

procedure SetItem(var Arr: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_ArrayTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_ArrayType.Inc'}{$ENDIF}; Index: Integer; {$IFDEF CDA_TypeString}const {$ENDIF}Item: {$IFDEF CDA_ExtTypes}{$INCLUDE '.\CDA_BaseTypeExt.Inc'}{$ELSE}{$INCLUDE '.\CDA_BaseType.Inc'}{$ENDIF});
begin
If CheckIndex(Arr,Index) then
  Arr.Arr[Index] := Item
else
  raise Exception.CreateFmt('GetItem: Index (%d) out of bounds.',[Index]);
end;