unit CountedDynArrays;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes;

type
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

{$DEFINE CDA_TypeBool}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeBool}

{$DEFINE CDA_TypeInteger}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeInteger}

{$DEFINE CDA_TypeDateTime}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeDateTime}

{$DEFINE CDA_TypeString}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeString}

{$DEFINE CDA_TypePointer}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypePointer}

{$DEFINE CDA_TypeObject}
type
  {$INCLUDE '.\CDA_ArrayType.inc'} = record
    Arr:    array of {$INCLUDE '.\CDA_BaseType.inc'};
    Count:  Integer;
    Data:   PtrInt;
  end;
  {$INCLUDE '.\CDA_PArrayType.inc'} = ^{$INCLUDE '.\CDA_ArrayType.inc'};

{$INCLUDE '.\CDA_Interface.inc'}
{$UNDEF CDA_TypeObject}

implementation

uses
  SysUtils;

{$DEFINE CDA_TypeBool}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeBool}

{$DEFINE CDA_TypeInteger}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeInteger}

{$DEFINE CDA_TypeDateTime}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeDateTime}

{$DEFINE CDA_TypeString}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeString}

{$DEFINE CDA_TypePointer}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypePointer}

{$DEFINE CDA_TypeObject}
  {$INCLUDE '.\CDA_Implementation.inc'}
{$UNDEF CDA_TypeObject}

end.


