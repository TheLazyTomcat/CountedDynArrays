{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of PtrUInt values

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
unit CountedDynArrayPtrUInt;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_FuncOverride_ItemCompare}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = PtrUInt;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayPtrUInt = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayPtrUInt = ^TCountedDynArrayPtrUInt;

  TCDAArrayType = TCountedDynArrayPtrUInt;
  PCDAArrayType = PCountedDynArrayPtrUInt;

  // aliases
  TCountedDynArrayOfPtrUInt = TCountedDynArrayPtrUInt;
  PCountedDynArrayOfPtrUInt = PCountedDynArrayPtrUInt;

  TPtrUIntCountedDynArray = TCountedDynArrayPtrUInt;
  PPtrUIntCountedDynArray = PCountedDynArrayPtrUInt;

  TCDAOfPtrUInt = TCountedDynArrayPtrUInt;
  PCDAOfPtrUInt = PCountedDynArrayPtrUInt;

  TCDAPtrUInt = TCountedDynArrayPtrUInt;
  PCDAPtrUInt = PCountedDynArrayPtrUInt;

  TPtrUIntCDA = TCountedDynArrayPtrUInt;
  PPtrUIntCDA = PCountedDynArrayPtrUInt;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  ListSorters;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = 0;

  CDA_ARRAY_NAME = 'AoPtrUInt';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer;
begin
If A < B then
  Result := -1
else If A > B then
  Result := +1
else
  Result := 0;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
