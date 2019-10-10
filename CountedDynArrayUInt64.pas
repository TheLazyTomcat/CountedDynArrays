{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of UInt64 values

  Version 1.2.2 (2019-09-22)
  
  Last changed 2019-10-10

  ©2018-2019 František Milt

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
unit CountedDynArrayUInt64;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_FuncOverride_ItemCompare}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = UInt64;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayUInt64 = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayUInt64 = ^TCountedDynArrayUInt64;

  // aliases
  TCountedDynArrayOfUInt64 = TCountedDynArrayUInt64;
  PCountedDynArrayOfUInt64 = PCountedDynArrayUInt64;

  TUInt64CountedDynArray = TCountedDynArrayUInt64;
  PUInt64CountedDynArray = PCountedDynArrayUInt64;

  TCDAArrayType = TCountedDynArrayUInt64;
  PCDAArrayType = PCountedDynArrayUInt64;

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
If Int64Rec(A).Hi < Int64Rec(B).Hi then
  Result := -1
else If Int64Rec(A).Hi > Int64Rec(B).Hi then
  Result := +1
else
  begin
    If Int64Rec(A).Lo < Int64Rec(B).Lo then
      Result := -1
    else If Int64Rec(A).Lo > Int64Rec(B).Lo then
      Result := +1
    else
      Result := 0;
  end;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
