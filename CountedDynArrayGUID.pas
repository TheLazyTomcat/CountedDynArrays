{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of TGUID values

  Version 1.4.2 (2024-05-03)

  Last changed 2024-05-03

  ©2018-2024 František Milt

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
  * AuxExceptions   - github.com/TheLazyTomcat/Lib.AuxExceptions
    AuxTypes        - github.com/TheLazyTomcat/Lib.AuxTypes
    BinaryStreaming - github.com/TheLazyTomcat/Lib.BinaryStreaming
    ListSorters     - github.com/TheLazyTomcat/Lib.ListSorters
    StrRect         - github.com/TheLazyTomcat/Lib.StrRect

  Library AuxExceptions is required only when rebasing local exception classes
  (see symbol CountedDynArrays_UseAuxExceptions for details).

  Library AuxExceptions might also be required as an indirect dependency.

  Indirect dependencies:
    AuxClasses  - github.com/TheLazyTomcat/Lib.AuxClasses
    SimpleCPUID - github.com/TheLazyTomcat/Lib.SimpleCPUID
    UInt64Utils - github.com/TheLazyTomcat/Lib.UInt64Utils
    WinFileInfo - github.com/TheLazyTomcat/Lib.WinFileInfo

===============================================================================}
unit CountedDynArrayGUID;

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
  TCDABaseType = TGUID;
  PCDABaseType = ^TCDABaseType;

  TCountedDynArrayGUID = record
  {$DEFINE CDA_Structure}
    {$INCLUDE '.\CountedDynArrays.inc'}
  {$UNDEF CDA_Structure}
  end;
  PCountedDynArrayGUID = ^TCountedDynArrayGUID;

  TCDAArrayType = TCountedDynArrayGUID;
  PCDAArrayType = PCountedDynArrayGUID;

  // aliases
  TCountedDynArrayOfGUID = TCountedDynArrayGUID;
  PCountedDynArrayOfGUID = PCountedDynArrayGUID;

  TGUIDCountedDynArray = TCountedDynArrayGUID;
  PGUIDCountedDynArray = PCountedDynArrayGUID;

  TCDAOfGUID = TCountedDynArrayGUID;
  PCDAOfGUID = PCountedDynArrayGUID;

  TCDAGUID = TCountedDynArrayGUID;
  PCDAGUID = PCountedDynArrayGUID;

  TGUIDCDA = TCountedDynArrayGUID;
  PGUIDCDA = PCountedDynArrayGUID;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters, StrRect, BinaryStreaming;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE: TGUID = '{00000000-0000-0000-0000-000000000000}';

  CDA_ARRAY_NAME = 'AoGUID';

//------------------------------------------------------------------------------

Function CDA_ItemCompare(A,B: TCDABaseType): Integer;
var
  i:  Integer;
begin
If A.D1 > B.D1 then
  Result := +1
else If A.D1 < B.D1 then
  Result := -1
else
  begin
    If A.D2 > B.D2 then
      Result := +1
    else If A.D2 < B.D2 then
      Result := -1
    else
      begin
        If A.D3 > B.D3 then
          Result := +1
        else If A.D3 < B.D3 then
          Result := -1
        else
          begin
            Result := 0;
            For i := Low(A.D4) to High(B.D4) do
              If A.D4[i] > B.D4[i] then
                begin
                  Result := +1;
                  Break{For i};
                end
              else If A.D4[i] < B.D4[i] then
                begin
                  Result := -1;
                  Break{For i};
                end;
          end;
      end;
  end;
end;

//------------------------------------------------------------------------------

procedure CDA_ItemWrite(Item: TCDABaseType; Stream: TStream);
begin
Stream_WriteUInt32(Stream,Item.D1);
Stream_WriteUInt16(Stream,Item.D2);
Stream_WriteUInt16(Stream,Item.D3);
Stream_WriteBuffer(Stream,Item.D4,SizeOf(Item.D4));
end;

//------------------------------------------------------------------------------

Function CDA_ItemRead(Stream: TStream): TCDABaseType;
begin
Result.D1 := Stream_GetUInt32(Stream);
Result.D2 := Stream_GetUInt16(Stream);
Result.D3 := Stream_GetUInt16(Stream);
Stream_ReadBuffer(Stream,Result.D4,SizeOf(Result.D4));
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

