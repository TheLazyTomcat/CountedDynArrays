{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted Dynamic Arrays

    Counted dynamic array of TGUID values

  Version 1.3 (2020-08-23)

  Last changed 2020-08-23

  ©2018-2020 František Milt

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
unit CountedDynArrayGUID;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

{$DEFINE CDA_FuncOverride_ItemCompare}

interface

uses
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

  // aliases
  TCountedDynArrayOfGUID = TCountedDynArrayGUID;
  PCountedDynArrayOfGUID = PCountedDynArrayGUID;

  TGUIDCountedDynArray = TCountedDynArrayGUID;
  PGUIDCountedDynArray = PCountedDynArrayGUID;

  TCDAArrayType = TCountedDynArrayGUID;
  PCDAArrayType = PCountedDynArrayGUID;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  ListSorters;

{$INCLUDE '.\CountedDynArrays_msgdis.inc'}

const
  CDA_DEFAULT_VALUE: TGUID = '{00000000-0000-0000-0000-000000000000}';

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

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.

