{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of Pointer values

  Version 1.3.1 (2021-09-15)

  Last changed 2021-09-15

  ©2018-2021 František Milt

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
    AuxTypes    - github.com/TheLazyTomcat/Lib.AuxTypes
    AuxClasses  - github.com/TheLazyTomcat/Lib.AuxClasses    
    ListSorters - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect     - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayPointer;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_FuncOverride_ItemCompare}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = Pointer;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayPointer = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayPointer = ^TCountedDynArrayPointer;

  TCDAArrayType = TCountedDynArrayPointer;
  PCDAArrayType = PCountedDynArrayPointer;

  // aliases
  TCountedDynArrayOfPointer = TCountedDynArrayPointer;
  PCountedDynArrayOfPointer = PCountedDynArrayPointer;

  TPointerCountedDynArray = TCountedDynArrayPointer;
  PPointerCountedDynArray = PCountedDynArrayPointer;

  TCDAOfPointer = TCountedDynArrayPointer;
  PCDAOfPointer = PCountedDynArrayPointer;

  TCDAPointer = TCountedDynArrayPointer;
  PCDAPointer = PCountedDynArrayPointer;

  TPointerCDA = TCountedDynArrayPointer;
  PPointerCDA = PCountedDynArrayPointer;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  ListSorters;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = nil;

  CDA_ARRAY_NAME = 'AoPointer';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer;{$IFDEF CanInline} inline; {$ENDIF}
begin
{$IFDEF FPCDWM}{$PUSH}W4055{$ENDIF}
If PtrUInt(A) < PtrUInt(B) then
  Result := -1
else If PtrUInt(A) > PtrUInt(B) then
  Result := +1
else
  Result := 0;
{$IFDEF FPCDWM}{$POP}{$ENDIF}
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
