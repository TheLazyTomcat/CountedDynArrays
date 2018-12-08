{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Counted dynamic array of UInt64 values

  ©František Milt 2018-12-08

  Version 1.0

  Dependencies:
    AuxTypes    - github.com/ncs-sniper/Lib.AuxTypes
    ListSorters - github.com/ncs-sniper/Lib.ListSorters

===============================================================================}
unit CountedDynArrayUInt64;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TUInt64CountedDynArray = record
    Arr:    array of UInt64;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PUInt64CountedDynArray = ^TUInt64CountedDynArray;

  TBaseType = UInt64;
  TArrayType = TUInt64CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: UInt64): Integer;
begin
Result := Integer(A - B);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
