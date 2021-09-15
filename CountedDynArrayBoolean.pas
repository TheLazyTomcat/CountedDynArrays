{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of Boolean values

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
unit CountedDynArrayBoolean;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_FuncOverride_ItemCompare}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = Boolean;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayBoolean = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayBoolean = ^TCountedDynArrayBoolean;

  TCDAArrayType = TCountedDynArrayBoolean;
  PCDAArrayType = PCountedDynArrayBoolean;

  // aliases
  TCountedDynArrayOfBoolean = TCountedDynArrayBoolean;
  PCountedDynArrayOfBoolean = PCountedDynArrayBoolean;

  TBooleanCountedDynArray = TCountedDynArrayBoolean;
  PBooleanCountedDynArray = PCountedDynArrayBoolean;

  TCDAOfBoolean = TCountedDynArrayBoolean;
  PCDAOfBoolean = PCountedDynArrayBoolean;

  TCDABoolean = TCountedDynArrayBoolean;
  PCDABoolean = PCountedDynArrayBoolean;

  TBooleanCDA = TCountedDynArrayBoolean;
  PBooleanCDA = PCountedDynArrayBoolean;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  ListSorters;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = False;

  CDA_ARRAY_NAME = 'AoBoolean';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer; {$IFDEF CanInline} inline;{$ENDIF}
begin
Result := Abs(Ord(A)) - Abs(Ord(B));
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

