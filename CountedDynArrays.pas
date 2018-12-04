unit CountedDynArrays;

{$IFDEF FPC}
  {$MODE ObjFPC}{$H+}
  {$INLINE ON}
  {$DEFINE CanInline}
{$ELSE}
  {$IF CompilerVersion >= 17 then}  // Delphi 2005+
    {$DEFINE CanInline}
  {$ELSE}
    {$UNDEF CanInline}
  {$IFEND}
{$ENDIF}

interface

uses
  AuxTypes;

type
  TInt32Array = record
    Arr:    array of Int32;
    Count:  Integer;
    Data:   PtrInt;
  end;

  TArrayType = TInt32Array;

{
  Array is only grown if current count + DeltaMin is larger than current capacity.

  agmSlow           - grow by 1
  agmLinear         - grow by GrowFactor (integer part of the float)
  agmFast           - grow by capacity * GrowFactor
  agmFastAttenuated - if capacity is below DYNARRAY_GROW_ATTENUATE_THRESHOLD,
                      then grow by capacity * GrowFactor
                    - if capacity is above or equal to DYNARRAY_GROW_ATTENUATE_THRESHOLD,
                      grow by 1/16 * DYNARRAY_GROW_ATTENUATE_THRESHOLD

  If mode is other than agmSlow and current capacity is 0, then new capacity is
  set to DYNARRAY_INITIAL_CAPACITY, irrespective of selected grow mode.
}
  TArrayGrowMode = (agmSlow, agmLinear, agmFast, agmFastAttenuated);

{
  asmKeepCap - array is not shrinked, capacity is preserved
  asmNormal  - if capacity is above DYNARRAY_INITIAL_CAPACITY and count is below capacity div 4,
               then capacity is set to capacity div 4, otherwise capacity is preserved
             - if capacity is below or equal to DYNARRAY_INITIAL_CAPACITY, then the array
               is not shinked unless the count is 0, in which case the new capacity is set to 0
  asmToCount - capacity is set to count
}
  TArrayShrinkMode = (asmKeepCap, asmNormal, asmToCount);

const
  DYNARRAY_INITIAL_CAPACITY         = 16;
  DYNARRAY_GROW_ATTENUATE_THRESHOLD = 16 * 1024 * 1024;

Function Length(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function Capacity(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function FreeCapacity(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function Count(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}

Function Low(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function High(const Arr: TArrayType): Integer; overload;{$IFDEF CanInline} inline; {$ENDIF}
Function CheckIndex(const Arr: TArrayType; Index: Integer): Boolean; overload;

procedure Init(var Arr: TArrayType); overload;
procedure SetLength(var Arr: TArrayType; NewLength: Integer); overload;
procedure SetCapacity(var Arr: TArrayType; NewCapacity: Integer); overload;{$IFDEF CanInline} inline; {$ENDIF}
procedure Clear(var Arr: TArrayType); overload;{$IFDEF CanInline} inline; {$ENDIF}

Function Grow(var Arr: TArrayType; GrowMode: TArrayGrowMode = agmFast; GrowFactor: Single = 2.0; DeltaMin: Integer = 1): Integer; overload;
procedure Shrink(var Arr: TArrayType; ShrinkMode: TArrayShrinkMode = asmNormal); overload;

procedure UniqueArray(var Arr: TArrayType); overload;{$IFDEF CanInline} inline; {$ENDIF}
procedure Copy(const Src: TArrayType; out Dst: TArrayType); overload;
Function Copy(const Src: TArrayType): TArrayType; overload;{$IFDEF CanInline} inline; {$ENDIF}

implementation

uses
  SysUtils;

Function Length(const Arr: TArrayType): Integer;
begin
Result := System.Length(Arr.Arr);
end;

//------------------------------------------------------------------------------

Function Capacity(const Arr: TArrayType): Integer;
begin
Result := System.Length(Arr.Arr);
end;

//------------------------------------------------------------------------------

Function FreeCapacity(const Arr: TArrayType): Integer;
begin
Result := System.Length(Arr.Arr) - Arr.Count;
end;

//------------------------------------------------------------------------------

Function Count(const Arr: TArrayType): Integer;
begin
Result := Arr.Count;
end;

//------------------------------------------------------------------------------

Function Low(const Arr: TArrayType): Integer;
begin
Result := System.Low(Arr.Arr);
end;

//------------------------------------------------------------------------------

Function High(const Arr: TArrayType): Integer;
begin
Result := Pred(Arr.Count);
end;

//------------------------------------------------------------------------------

Function CheckIndex(const Arr: TArrayType; Index: Integer): Boolean;
begin
Result := (Index >= System.Low(Arr.Arr)) and (Index < Arr.Count);
end;

//------------------------------------------------------------------------------

procedure Init(var Arr: TArrayType);
begin
System.SetLength(Arr.Arr,0);
Arr.Count := 0;
Arr.Data := 0;
end;

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

procedure SetCapacity(var Arr: TArrayType; NewCapacity: Integer);
begin
SetLength(Arr,NewCapaCity);
end;

//------------------------------------------------------------------------------

procedure Clear(var Arr: TArrayType);
begin
SetLength(Arr,0);
end;

//------------------------------------------------------------------------------

Function Grow(var Arr: TArrayType; GrowMode: TArrayGrowMode = agmFast; GrowFactor: Single = 2.0; DeltaMin: Integer = 1): Integer;
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

procedure Shrink(var Arr: TArrayType; ShrinkMode: TArrayShrinkMode = asmNormal);
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

procedure UniqueArray(var Arr: TArrayType);
begin
SetLength(Arr,Capacity(Arr));
end;

//------------------------------------------------------------------------------

procedure Copy(const Src: TArrayType; out Dst: TArrayType);
begin
Dst.Arr := System.Copy(Src.Arr);
Dst.Count := Src.Count;
Dst.Data := Src.Data;
end;

//------------------------------------------------------------------------------

Function Copy(const Src: TArrayType): TArrayType;
begin
Copy(Src,Result);
end;

end.
