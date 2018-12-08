{-------------------------------------------------------------------------------

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

-------------------------------------------------------------------------------}
{===============================================================================

  Counted dynamic arrays

    Counted dynamic array of Float32 (Single) values

  ©František Milt 2018-12-08

  Version 1.0

  Dependencies:
    AuxTypes    - github.com/ncs-sniper/Lib.AuxTypes
    ListSorters - github.com/ncs-sniper/Lib.ListSorters

===============================================================================}
unit CountedDynArrayFloat32;

{$INCLUDE '.\CountedDynArrays_defs.inc'}

interface

uses
  AuxTypes,
  CountedDynArrays;

type
  TFloat32CountedDynArray = record
    Arr:    array of Float32;
    Count:  Integer;
    Data:   PtrInt;
  end;
  PFloat32CountedDynArray = ^TFloat32CountedDynArray;

  TBaseType = Float32;
  TArrayType = TFloat32CountedDynArray;

{$DEFINE CDA_Interface}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Interface}


implementation

uses
  SysUtils,
  ListSorters;

Function CDA_CompareFunc(A,B: Float32): Integer;
begin
If A > B then Result := 1
  else If A < B then Result := -1
    else Result := 0;
end;

//------------------------------------------------------------------------------

{$DEFINE CDA_Implementation}
{$INCLUDE '.\CountedDynArrays.inc'}
{$UNDEF CDA_Implementation}

end.
