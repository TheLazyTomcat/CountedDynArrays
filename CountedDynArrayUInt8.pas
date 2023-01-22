{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of UInt8 values

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
unit CountedDynArrayUInt8;

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
  TCDABaseType = UInt8;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayUInt8 = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayUInt8 = ^TCountedDynArrayUInt8;

  TCDAArrayType = TCountedDynArrayUInt8;
  PCDAArrayType = PCountedDynArrayUInt8;

  // aliases
  TCountedDynArrayOfUInt8 = TCountedDynArrayUInt8;
  PCountedDynArrayOfUInt8 = PCountedDynArrayUInt8;

  TUInt8CountedDynArray = TCountedDynArrayUInt8;
  PUInt8CountedDynArray = PCountedDynArrayUInt8;

  TCDAOfUInt8 = TCountedDynArrayUInt8;
  PCDAOfUInt8 = PCountedDynArrayUInt8;

  TCDAUInt8 = TCountedDynArrayUInt8;
  PCDAUInt8 = PCountedDynArrayUInt8;

  TUInt8CDA = TCountedDynArrayUInt8;
  PUInt8CDA = PCountedDynArrayUInt8;

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

  CDA_ARRAY_NAME = 'AoUInt8';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer; {$IFDEF CanInline} inline; {$ENDIF}
begin
Result := Integer(A - B);
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteUInt8(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_ReadUInt8(Stream);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

