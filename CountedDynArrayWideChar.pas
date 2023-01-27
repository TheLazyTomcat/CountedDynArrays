{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of WideChar values

  Version 1.4.1 (2023-01-27)

  Last changed 2023-01-27

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
unit CountedDynArrayWideChar;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_CaseSensitiveBaseType}

{$DEFINE CDA_FuncOverride_ItemCompare}
{$DEFINE CDA_FuncOverride_ItemWrite}
{$DEFINE CDA_FuncOverride_ItemRead}

interface

uses
  Classes,
  AuxTypes,
  CountedDynArrays;

type
  TCDABaseType = WideChar;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayWideChar = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayWideChar = ^TCountedDynArrayWideChar;

  TCDAArrayType = TCountedDynArrayWideChar;
  PCDAArrayType = PCountedDynArrayWideChar;

  // aliases
  TCountedDynArrayOfWideChar = TCountedDynArrayWideChar;
  PCountedDynArrayOfWideChar = PCountedDynArrayWideChar;

  TWideCharCountedDynArray = TCountedDynArrayWideChar;
  PWideCharCountedDynArray = PCountedDynArrayWideChar;

  TCDAOfWideChar = TCountedDynArrayWideChar;
  PCDAOfWideChar = PCountedDynArrayWideChar;

  TCDAWideChar = TCountedDynArrayWideChar;
  PCDAWideChar = PCountedDynArrayWideChar;

  TWideCharCDA = TCountedDynArrayWideChar;
  PWideCharCDA = PCountedDynArrayWideChar;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses 
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE = TCDABaseType(#0);

  CDA_ARRAY_NAME = 'AoWideChar';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType; CaseSensitive: Boolean): Integer;{$IFDEF CanInline} inline;{$ENDIF}
begin
Result := WideStringCompare(A,B,CaseSensitive);
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteWideChar(Stream,Item);
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result := Stream_ReadWideChar(Stream);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
