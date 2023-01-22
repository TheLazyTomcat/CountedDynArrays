{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of UInt64 values

  Version 1.4 (2023-01-22)

  Last changed 2023-01-22

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
    AuxClasses         - github.com/TheLazyTomcat/Lib.AuxClasses
    AuxTypes           - github.com/TheLazyTomcat/Lib.AuxTypes
    BinaryStreaming    - github.com/TheLazyTomcat/Lib.BinaryStreaming
    ListSorters        - github.com/TheLazyTomcat/Lib.ListSorters
    StaticMemoryStream - github.com/TheLazyTomcat/Lib.StaticMemoryStream
    StrRect            - github.com/TheLazyTomcat/Lib.StrRect

===============================================================================}
unit CountedDynArrayUInt64;

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
  TCDABaseType = UInt64;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayUInt64 = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayUInt64 = ^TCountedDynArrayUInt64;

  TCDAArrayType = TCountedDynArrayUInt64;
  PCDAArrayType = PCountedDynArrayUInt64;

  // aliases
  TCountedDynArrayOfUInt64 = TCountedDynArrayUInt64;
  PCountedDynArrayOfUInt64 = PCountedDynArrayUInt64;

  TUInt64CountedDynArray = TCountedDynArrayUInt64;
  PUInt64CountedDynArray = PCountedDynArrayUInt64;

  TCDAOfUInt64 = TCountedDynArrayUInt64;
  PCDAOfUInt64 = PCountedDynArrayUInt64;

  TCDAUInt64 = TCountedDynArrayUInt64;
  PCDAUInt64 = PCountedDynArrayUInt64;

  TUInt64CDA = TCountedDynArrayUInt64;
  PUInt64CDA = PCountedDynArrayUInt64;

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

  CDA_ARRAY_NAME = 'AoUInt64';

//------------------------------------------------------------------------------

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

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteUInt64(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_ReadUInt64(Stream);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
