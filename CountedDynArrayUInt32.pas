{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Counted dynamic array of UInt32 values

  ©František Milt 2018-12-08

  Version 1.0

  Dependencies:
    AuxTypes    - github.com/ncs-sniper/Lib.AuxTypes
    ListSorters - github.com/ncs-sniper/Lib.ListSorters

===============================================================================}
unit CountedDynArrayUInt32;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TUInt32CountedDynArray = record
    Arr:    array of UInt32;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PUInt32CountedDynArray = ^TUInt32CountedDynArray;

  TCDABaseType = UInt32;
  PCDABaseType = PUInt32;

  TCDAArrayType = TUInt32CountedDynArray;
  PCDAArrayType = PUInt32CountedDynArray;  

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}

implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: UInt32): Integer;
begin
Result := Integer(B - A);
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
