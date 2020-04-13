import { Injectable } from '@angular/core';
import { Observable, BehaviorSubject } from 'rxjs'
import { filter, map } from 'rxjs/operators'

declare var Module: any;

// import * as Module from './../../wasm/main.js';
import "!!file-loader?name=wasm/main.wasm!../../wasm/main.wasm";
// import "!!arraybuffer-loader?name=wasm/main.wasm!type=javascript/auto!../../wasm/main.wasm";

@Injectable({
  providedIn: 'root'
})
export class WasmService {

  module: any;

  wasmReady = new BehaviorSubject<boolean>(false);

  constructor() {
    this.instantiateWasm('wasm/main.wasm');
  }

  private async instantiateWasm(url: string) {
    // fetch the wasm file
    const wasmFile = await fetch(url);

    // convert it into a binary array
    const buffer = await wasmFile.arrayBuffer();
    const binary = new Uint8Array(buffer);

    // create module arguments
    // including the wasm-file
    const moduleArgs = {
      wasmBinary: binary,
      onRuntimeInitialized: () => {
        this.wasmReady.next(true);
        console.log("Wasm Module initialized !");
      }
    };

    // instantiate the module
    this.module = Module(moduleArgs);
  }

  public PenguinGame(size_hex: number, nb_peng: number): Observable<any> {
    return this.wasmReady.pipe(filter(value => value === true)).pipe(
      map(() => {
        return new this.module.PenguinGame(size_hex, nb_peng);
      })
    )
  }

  public getBoard(): any {
    return this.module.getBoard();
  }

}
