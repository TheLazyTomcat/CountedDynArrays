{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of PtrUInt values

  ©František Milt 2019-08-14

  Version 1.2.0

  Contacts:
    František Milt: frantisek.milt@gmail.com

  Support:
    If you find this code useful, please consider supporting its author(s) by
    making a small donation using the following link(s):

      https://www.paypal.me/FMilt

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

  // aliases
  TCountedDynArrayOfPtrUInt = TCountedDynArrayPtrUInt;
  PCountedDynArrayOfPtrUInt = PCountedDynArrayPtrUInt;

  TPtrUIntCountedDynArray = TCountedDynArrayPtrUInt;
  PPtrUIntCountedDynArray = PCountedDynArrayPtrUInt;

  TCDAArrayType = TCountedDynArrayPtrUInt;
  PCDAArrayType = PCountedDynArrayPtrUInt;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

Function CDA_ItemCompare(A,B: TCDABaseType): Integer;
begin
If A < B then
  Result := +1
else If A > B then
  Result := -1
else
  Result := 0;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
