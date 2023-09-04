{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of UInt32 values

  Version 1.4.1 (2023-01-27)

  Last changed 2023-09-04

  ©2018-2023 František Milt

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
    AuxClasses      - github.com/TheLazyTomcat/Lib.AuxClasses
    AuxTypes        - github.com/TheLazyTomcat/Lib.AuxTypes
    BinaryStreaming - github.com/TheLazyTomcat/Lib.BinaryStreaming
    ListSorters     - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect         - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayUInt32;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_FuncOverride_ItemCompare}
{$DEFINE CDA_FuncOverride_ItemWrite}
{$DEFINE CDA_FuncOverride_ItemRead}

interface

uses
  Classes,
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = UInt32;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayUInt32 = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayUInt32 = ^TCountedDynArrayUInt32;

  TCDAArrayType = TCountedDynArrayUInt32;
  PCDAArrayType = PCountedDynArrayUInt32;

  // aliases
  TCountedDynArrayOfUInt32 = TCountedDynArrayUInt32;
  PCountedDynArrayOfUInt32 = PCountedDynArrayUInt32;

  TUInt32CountedDynArray = TCountedDynArrayUInt32;
  PUInt32CountedDynArray = PCountedDynArrayUInt32;

  TCDAOfUInt32 = TCountedDynArrayUInt32;
  PCDAOfUInt32 = PCountedDynArrayUInt32;

  TCDAUInt32 = TCountedDynArrayUInt32;
  PCDAUInt32 = PCountedDynArrayUInt32;

  TUInt32CDA = TCountedDynArrayUInt32;
  PUInt32CDA = PCountedDynArrayUInt32;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses 
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = 0;

  CDA_ARRAY_NAME = 'AoUInt32';

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

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteUInt32(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_GetUInt32(Stream);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
