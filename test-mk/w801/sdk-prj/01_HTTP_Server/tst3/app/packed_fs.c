#include <stddef.h>
#include <string.h>
#include <time.h>

#if defined(__cplusplus)
extern "C" {
#endif
const char *mg_unlist(size_t no);
const char *mg_unpack(const char *, size_t *, time_t *);
#if defined(__cplusplus)
}
#endif

static const unsigned char v1[] = {
  60,  33,  68,  79,  67,  84,  89,  80,  69,  32, 104, 116, // <!DOCTYPE ht
 109, 108,  62,  10,  60, 104, 116, 109, 108,  32, 108,  97, // ml>.<html la
 110, 103,  61,  34, 101, 110,  34,  62,  10,  32,  32,  60, // ng="en">.  <
 104, 101,  97, 100,  62,  10,  32,  32,  32,  32,  60, 116, // head>.    <t
 105, 116, 108, 101,  62, 101, 120,  97, 109, 112, 108, 101, // itle>example
  32,  87,  56,  48,  49,  32,  43,  32, 109, 111, 110, 103, //  W801 + mong
 111, 111, 115, 101,  32,  61,  32,  72,  84,  84,  80,  32, // oose = HTTP 
  83, 101, 114, 118, 101, 114,  60,  47, 116, 105, 116, 108, // Server</titl
 101,  62,  10,  32,  32,  32,  32,  60, 109, 101, 116,  97, // e>.    <meta
  32,  99, 104,  97, 114, 115, 101, 116,  61,  34, 117, 116, //  charset="ut
 102,  45,  56,  34,  32,  47,  62,  10,  32,  32,  32,  32, // f-8" />.    
  60, 109, 101, 116,  97,  32, 104, 116, 116, 112,  45, 101, // <meta http-e
 113, 117, 105, 118,  61,  34,  88,  45,  85,  65,  45,  67, // quiv="X-UA-C
 111, 109, 112,  97, 116, 105,  98, 108, 101,  34,  32,  99, // ompatible" c
 111, 110, 116, 101, 110, 116,  61,  34,  73,  69,  61, 101, // ontent="IE=e
 100, 103, 101,  34,  32,  47,  62,  10,  32,  32,  32,  32, // dge" />.    
  60, 109, 101, 116,  97,  32, 110,  97, 109, 101,  61,  34, // <meta name="
 118, 105, 101, 119, 112, 111, 114, 116,  34,  32,  99, 111, // viewport" co
 110, 116, 101, 110, 116,  61,  34, 119, 105, 100, 116, 104, // ntent="width
  61, 100, 101, 118, 105,  99, 101,  45, 119, 105, 100, 116, // =device-widt
 104,  44,  32, 105, 110, 105, 116, 105,  97, 108,  45, 115, // h, initial-s
  99,  97, 108, 101,  61,  49,  46,  48,  34,  32,  47,  62, // cale=1.0" />
  10,  32,  32,  32,  32,  60, 115, 116, 121, 108, 101,  62, // .    <style>
  10,  32,  32,  32,  32,  32,  32,  35,  99, 111, 110, 116, // .      #cont
  97, 105, 110, 101, 114,  32, 123,  32, 109,  97, 114, 103, // ainer { marg
 105, 110,  45, 114, 105, 103, 104, 116,  58,  32,  97, 117, // in-right: au
 116, 111,  59,  32, 109,  97, 114, 103, 105, 110,  45, 108, // to; margin-l
 101, 102, 116,  58,  32,  97, 117, 116, 111,  59,  32, 109, // eft: auto; m
  97, 120,  45, 119, 105, 100, 116, 104,  58,  32,  52,  56, // ax-width: 48
  48, 112, 120,  59,  32, 125,  10,  32,  32,  32,  32,  32, // 0px; }.     
  32,  35, 105, 110, 102, 111,  32, 123,  32,  98,  97,  99, //  #info { bac
 107, 103, 114, 111, 117, 110, 100,  58,  32,  35, 101,  48, // kground: #e0
 102,  48, 102,  48,  59,  32,  98, 111, 114, 100, 101, 114, // f0f0; border
  45, 114,  97, 100, 105, 117, 115,  58,  32,  46,  53, 101, // -radius: .5e
 109,  59,  32, 112,  97, 100, 100, 105, 110, 103,  58,  32, // m; padding: 
  50, 101, 109,  59,  32,  32, 125,  10,  32,  32,  32,  32, // 2em;  }.    
  32,  32,  35, 115, 116,  97, 116, 105,  99,  44,  32,  35, //   #static, #
 108, 105, 118, 101,  32, 123,  32,  98,  97,  99, 107, 103, // live { backg
 114, 111, 117, 110, 100,  58,  32,  35, 102,  48, 102,  48, // round: #f0f0
 102,  48,  59,  32,  98, 111, 114, 100, 101, 114,  45, 114, // f0; border-r
  97, 100, 105, 117, 115,  58,  32,  46,  53, 101, 109,  59, // adius: .5em;
  32, 112,  97, 100, 100, 105, 110, 103,  58,  32,  48,  46, //  padding: 0.
  53, 101, 109,  59,  32, 109,  97, 120,  45, 104, 101, 105, // 5em; max-hei
 103, 104, 116,  58,  32,  49,  48, 101, 109,  59,  32, 111, // ght: 10em; o
 118, 101, 114, 102, 108, 111, 119,  58,  32,  97, 117, 116, // verflow: aut
 111,  59,  32, 104, 101, 105, 103, 104, 116,  58,  32,  49, // o; height: 1
  48,  48,  37,  59,  32, 125,  10,  32,  32,  32,  32,  32, // 00%; }.     
  32,  35, 119, 114,  97, 112, 112, 101, 114,  32, 123,  32, //  #wrapper { 
 100, 105, 115, 112, 108,  97, 121,  58,  32, 102, 108, 101, // display: fle
 120,  59,  32, 106, 117, 115, 116, 105, 102, 121,  45,  99, // x; justify-c
 111, 110, 116, 101, 110, 116,  58,  32, 102, 108, 101, 120, // ontent: flex
  45, 101, 118, 101, 110, 108, 121,  59,  32, 109,  97, 114, // -evenly; mar
 103, 105, 110,  45, 116, 111, 112,  58,  32,  49, 101, 109, // gin-top: 1em
  59,  32, 125,  10,  32,  32,  32,  32,  60,  47, 115, 116, // ; }.    </st
 121, 108, 101,  62,  10,  32,  32,  60,  47, 104, 101,  97, // yle>.  </hea
 100,  62,  10,  32,  32,  60,  98, 111, 100, 121,  62,  10, // d>.  <body>.
  32,  32,  32,  32,  60, 100, 105, 118,  32, 105, 100,  61, //     <div id=
  34,  99, 111, 110, 116,  97, 105, 110, 101, 114,  34,  62, // "container">
  10,  32,  32,  32,  32,  32,  32,  60, 100, 105, 118,  32, // .      <div 
 105, 100,  61,  34, 105, 110, 102, 111,  34,  62,  10,  32, // id="info">. 
  32,  32,  32,  32,  32,  32,  32,  32, 208, 188, 208, 184, //         ....
 208, 186, 209, 128, 208, 190, 208, 186, 208, 190, 208, 189, // ............
 209, 130, 209, 128, 208, 190, 208, 187, 208, 187, 208, 181, // ............
 209, 128,  32,  87,  56,  48,  49,  32,  43,  32, 109, 111, // .. W801 + mo
 110, 103, 111, 111, 115, 101,  32,  61,  32,  72,  84,  84, // ngoose = HTT
  80,  32,  83, 101, 114, 118, 101, 114,  10,  32,  32,  32, // P Server.   
  32,  32,  32,  32,  32,  60,  98, 114,  47,  62,  60,  98, //      <br/><b
 114,  47,  62,  10,  32,  32,  32,  32,  32,  32,  32,  32, // r/>.        
  32, 209, 129, 208, 190, 208, 177, 209, 128, 208, 176, 208, //  ...........
 189, 208, 190,  32, 208, 184, 208, 183,  32, 208, 191, 209, // ... .... ...
 128, 208, 184, 208, 188, 208, 181, 209, 128, 208, 176,  32, // ........... 
  60,  97,  32, 104, 114, 101, 102,  61,  34, 104, 116, 116, // <a href="htt
 112, 115,  58,  47,  47, 109, 111, 110, 103, 111, 111, 115, // ps://mongoos
 101,  46, 119, 115,  47, 100, 111,  99, 117, 109, 101, 110, // e.ws/documen
 116,  97, 116, 105, 111, 110,  47, 116, 117, 116, 111, 114, // tation/tutor
 105,  97, 108, 115,  47, 119, 101,  98, 117, 105,  45, 112, // ials/webui-p
 117, 115, 104,  47,  34,  62, 119, 101,  98, 117, 105,  45, // ush/">webui-
 112, 117, 115, 104,  60,  47,  97,  62,  10,  32,  32,  32, // push</a>.   
  32,  32,  32,  32,  32,  60,  98, 114,  47,  62,  60,  98, //      <br/><b
 114,  47,  62,  10,  32,  32,  32,  32,  32,  32,  32,  32, // r/>.        
  32, 208, 146,  32, 208, 177, 208, 187, 208, 190, 208, 186, //  .. ........
 208, 181,  32, 115, 116,  97, 116, 105,  99,  32, 208, 189, // .. static ..
 208, 184, 208, 182, 208, 181,  32, 208, 191, 208, 190, 208, // ...... .....
 186, 208, 176, 208, 183, 208, 176, 208, 189,  32, 209, 132, // ......... ..
 208, 176, 208, 185, 208, 187,  32, 108, 111, 103,  46, 116, // ...... log.t
 120, 116,  46,  10,  32,  32,  32,  32,  32,  32,  32,  32, // xt..        
  32, 208, 154, 208, 190, 208, 180,  32,  74,  83,  32, 208, //  ...... JS .
 189, 208, 176,  32, 209, 141, 209, 130, 208, 190, 208, 185, // ... ........
  32, 209, 129, 209, 130, 209, 128, 208, 176, 208, 189, 208, //  ...........
 184, 209, 134, 208, 181,  32, 209, 129, 208, 189, 208, 176, // ..... ......
 209, 135, 208, 176, 208, 187, 208, 176,  32, 208, 184, 208, // ........ ...
 183, 208, 178, 208, 187, 208, 181, 208, 186, 208, 176, 208, // ............
 181, 209, 130,  32,  47,  97, 112, 105,  47, 108, 111, 103, // ... /api/log
  47, 115, 116,  97, 116, 105,  99,  44,  32, 208, 186, 208, // /static, ...
 190, 209, 130, 208, 190, 209, 128, 209, 139, 208, 185,  32, // ........... 
  10,  32,  32,  32,  32,  32,  32,  32,  32,  32, 208, 178, // .         ..
 208, 190, 208, 183, 208, 178, 209, 128, 208, 176, 209, 137, // ............
 208, 176, 208, 181, 209, 130,  32, 209, 129, 208, 190, 208, // ...... .....
 180, 208, 181, 209, 128, 208, 182, 208, 184, 208, 188, 208, // ............
 190, 208, 181,  32, 108, 111, 103,  46, 116, 120, 116,  44, // ... log.txt,
  32,  10,  32,  32,  32,  32,  32,  32,  32,  32,  32, 208, //  .         .
 183, 208, 176, 209, 130, 208, 181, 208, 188,  32, 208, 184, // ......... ..
 208, 183, 208, 178, 208, 187, 208, 181, 208, 186, 208, 176, // ............
 208, 181, 209, 130,  32,  47,  97, 112, 105,  47, 108, 111, // .... /api/lo
 103,  47, 108, 105, 118, 101,  44,  32, 208, 186, 208, 190, // g/live, ....
 209, 130, 208, 190, 209, 128, 209, 139, 208, 185,  32, 208, // .......... .
 191, 208, 181, 209, 128, 208, 181, 208, 180, 208, 176, 208, // ............
 181, 209, 130,  32, 209, 132, 209, 128, 208, 176, 208, 179, // ... ........
 208, 188, 208, 181, 208, 189, 209, 130, 209, 139,  32, 208, // .......... .
 180, 208, 176, 208, 189, 208, 189, 209, 139, 209, 133,  10, // ............
  32,  32,  32,  32,  32,  32,  32,  32,  32, 208, 191, 208, //          ...
 190,  32, 208, 188, 208, 181, 209, 128, 208, 181,  32, 208, // . ........ .
 184, 209, 133,  32, 208, 191, 208, 190, 209, 129, 209, 130, // ... ........
 209, 131, 208, 191, 208, 187, 208, 181, 208, 189, 208, 184, // ............
 209, 143,  32,  40, 208, 182, 208, 184, 208, 178, 208, 190, // .. (........
 208, 185,  32, 208, 182, 209, 131, 209, 128, 208, 189, 208, // .. .........
 176, 208, 187,  41,  46,  10,  32,  32,  32,  32,  32,  32, // ...)..      
  32,  32,  60,  98, 114,  47,  62,  60,  98, 114,  47,  62, //   <br/><br/>
  10,  32,  32,  32,  32,  32,  32,  32,  32, 208, 146, 209, // .        ...
 139,  32, 209, 130, 208, 176, 208, 186, 208, 182, 208, 181, // . ..........
  32, 208, 188, 208, 190, 208, 182, 208, 181, 209, 130, 208, //  ...........
 181,  32, 208, 184, 209, 129, 208, 191, 208, 190, 208, 187, // . ..........
 209, 140, 208, 183, 208, 190, 208, 178, 208, 176, 209, 130, // ............
 209, 140,  32, 209, 131, 209, 130, 208, 184, 208, 187, 208, // .. .........
 184, 209, 130, 209, 131,  32, 208, 186, 208, 190, 208, 188, // ..... ......
 208, 176, 208, 189, 208, 180, 208, 189, 208, 190, 208, 185, // ............
  32, 209, 129, 209, 130, 209, 128, 208, 190, 208, 186, 208, //  ...........
 184,  32,  10,  32,  32,  32,  32,  32,  32,  32,  32,  60, // . .        <
  99, 111, 100, 101,  62,  99, 117, 114, 108,  60,  47,  99, // code>curl</c
 111, 100, 101,  62,  44,  32, 209, 135, 209, 130, 208, 190, // ode>, ......
 208, 177, 209, 139,  32, 209, 131, 208, 178, 208, 184, 208, // .... .......
 180, 208, 181, 209, 130, 209, 140,  32, 208, 182, 209, 131, // ....... ....
 209, 128, 208, 189, 208, 176, 208, 187, 209, 139,  58,  10, // ..........:.
  32,  32,  32,  32,  32,  32,  32,  32,  40, 208, 178,  32, //         (.. 
 208, 191, 209, 128, 208, 184, 208, 188, 208, 181, 209, 128, // ............
 208, 181,  32,  73,  80,  32,  49,  57,  50,  46,  49,  54, // .. IP 192.16
  56,  46,  49,  46,  56,  55,  44,  32, 209, 131,  32, 208, // 8.1.87, .. .
 178, 208, 176, 209, 129,  32, 208, 188, 208, 190, 208, 182, // ..... ......
 208, 181, 209, 130,  32, 208, 177, 209, 139, 209, 130, 209, // .... .......
 140,  32, 209, 129, 208, 178, 208, 190, 209, 145,  41,  32, // . ........) 
  10,  32,  32,  32,  32,  32,  32,  32,  32,  60,  98, 114, // .        <br
  47,  62,  60,  99, 111, 100, 101,  62,  99, 117, 114, 108, // /><code>curl
  32,  49,  57,  50,  46,  49,  54,  56,  46,  49,  46,  56, //  192.168.1.8
  55,  47,  97, 112, 105,  47, 108, 111, 103,  47, 115, 116, // 7/api/log/st
  97, 116, 105,  99,  60,  47,  99, 111, 100, 101,  62,  10, // atic</code>.
  32,  32,  32,  32,  32,  32,  32,  32,  60,  98, 114,  47, //         <br/
  62,  60,  99, 111, 100, 101,  62,  99, 117, 114, 108,  32, // ><code>curl 
  49,  57,  50,  46,  49,  54,  56,  46,  49,  46,  56,  55, // 192.168.1.87
  47,  97, 112, 105,  47, 108, 111, 103,  47, 108, 105, 118, // /api/log/liv
 101,  60,  47,  99, 111, 100, 101,  62,  10,  32,  32,  32, // e</code>.   
  32,  32,  32,  60,  47, 100, 105, 118,  62,  10,  32,  32, //    </div>.  
  32,  32,  32,  32,  60, 100, 105, 118,  32, 105, 100,  61, //     <div id=
  34, 119, 114,  97, 112, 112, 101, 114,  34,  62,  10,  32, // "wrapper">. 
  32,  32,  32,  32,  32,  32,  32,  60, 100, 105, 118,  32, //        <div 
 115, 116, 121, 108, 101,  61,  34, 119, 105, 100, 116, 104, // style="width
  58,  32,  53,  48,  37,  34,  62,  60,  98,  62,  83, 116, // : 50%"><b>St
  97, 116, 105,  99,  60,  47,  98,  62,  60, 112, 114, 101, // atic</b><pre
  32, 105, 100,  61,  34, 115, 116,  97, 116, 105,  99,  34, //  id="static"
  62,  60,  47, 112, 114, 101,  62,  60,  47, 100, 105, 118, // ></pre></div
  62,  10,  32,  32,  32,  32,  32,  32,  32,  32,  60, 100, // >.        <d
 105, 118,  32, 115, 116, 121, 108, 101,  61,  34, 119, 105, // iv style="wi
 100, 116, 104,  58,  32,  49, 101, 109,  59,  34,  62,  60, // dth: 1em;"><
  47, 100, 105, 118,  62,  10,  32,  32,  32,  32,  32,  32, // /div>.      
  32,  32,  60, 100, 105, 118,  32, 115, 116, 121, 108, 101, //   <div style
  61,  34, 119, 105, 100, 116, 104,  58,  32,  53,  48,  37, // ="width: 50%
  34,  62,  60,  98,  62,  76, 105, 118, 101,  60,  47,  98, // "><b>Live</b
  62,  60, 112, 114, 101,  32, 105, 100,  61,  34, 108, 105, // ><pre id="li
 118, 101,  34,  62,  60,  47, 112, 114, 101,  62,  60,  47, // ve"></pre></
 100, 105, 118,  62,  10,  32,  32,  32,  32,  32,  32,  60, // div>.      <
  47, 100, 105, 118,  62,  10,  32,  32,  32,  32,  60,  47, // /div>.    </
 100, 105, 118,  62,  10,  32,  32,  60,  47,  98, 111, 100, // div>.  </bod
 121,  62,  10,  32,  32,  60, 115,  99, 114, 105, 112, 116, // y>.  <script
  62,  10,  32,  32,  32,  32, 115, 101, 116,  73, 110, 116, // >.    setInt
 101, 114, 118,  97, 108,  40, 102,  44,  50,  48,  48,  41, // erval(f,200)
  59,  10,  32,  32,  32,  32, 118,  97, 114,  32, 102,  32, // ;.    var f 
  61,  32, 102, 117, 110,  99, 116, 105, 111, 110,  40, 114, // = function(r
  41,  32, 123,  10,  32,  32,  32,  32,  32,  32, 114, 101, // ) {.      re
 116, 117, 114, 110,  32, 114,  46, 114, 101,  97, 100,  40, // turn r.read(
  41,  46, 116, 104, 101, 110,  40, 102, 117, 110,  99, 116, // ).then(funct
 105, 111, 110,  40, 114, 101, 115, 117, 108, 116,  41,  32, // ion(result) 
 123,  10,  32,  32,  32,  32,  32,  32,  32,  32, 118,  97, // {.        va
 114,  32, 100,  97, 116,  97,  32,  61,  32,  83, 116, 114, // r data = Str
 105, 110, 103,  46, 102, 114, 111, 109,  67, 104,  97, 114, // ing.fromChar
  67, 111, 100, 101,  46,  97, 112, 112, 108, 121,  40, 110, // Code.apply(n
 117, 108, 108,  44,  32, 114, 101, 115, 117, 108, 116,  46, // ull, result.
 118,  97, 108, 117, 101,  41,  59,  10,  32,  32,  32,  32, // value);.    
  32,  32,  32,  32, 100, 111,  99, 117, 109, 101, 110, 116, //     document
  46, 103, 101, 116,  69, 108, 101, 109, 101, 110, 116,  66, // .getElementB
 121,  73, 100,  40,  39, 108, 105, 118, 101,  39,  41,  46, // yId('live').
 105, 110, 110, 101, 114,  84, 101, 120, 116,  32,  61,  32, // innerText = 
 100,  97, 116,  97,  59,  32,  32,  47,  47,  32, 108, 105, // data;  // li
 118, 101,  32, 108, 111, 103,  10,  32,  32,  32,  32,  32, // ve log.     
  32,  32,  32, 105, 102,  32,  40,  33, 114, 101, 115, 117, //    if (!resu
 108, 116,  46, 100, 111, 110, 101,  41,  32, 102,  40, 114, // lt.done) f(r
  41,  59,  32,  32,  47,  47,  32,  82, 101,  97, 100,  32, // );  // Read 
 110, 101, 120, 116,  32,  99, 104, 117, 110, 107,  10,  32, // next chunk. 
  32,  32,  32,  32,  32, 125,  41,  59,  10,  32,  32,  32, //      });.   
  32, 125,  59,  10,  32,  32,  32,  32, 119, 105, 110, 100, //  };.    wind
 111, 119,  46, 111, 110, 108, 111,  97, 100,  32,  61,  32, // ow.onload = 
 101, 118,  32,  61,  62,  32, 102, 101, 116,  99, 104,  40, // ev => fetch(
  39,  47,  97, 112, 105,  47, 108, 111, 103,  47, 115, 116, // '/api/log/st
  97, 116, 105,  99,  39,  41,  10,  32,  32,  32,  32,  32, // atic').     
  32,  46, 116, 104, 101, 110,  40, 114,  32,  61,  62,  32, //  .then(r => 
 114,  46, 116, 101, 120, 116,  40,  41,  41,  10,  32,  32, // r.text()).  
  32,  32,  32,  32,  46, 116, 104, 101, 110,  40, 114,  32, //     .then(r 
  61,  62,  32, 123,  32, 100, 111,  99, 117, 109, 101, 110, // => { documen
 116,  46, 103, 101, 116,  69, 108, 101, 109, 101, 110, 116, // t.getElement
  66, 121,  73, 100,  40,  39, 115, 116,  97, 116, 105,  99, // ById('static
  39,  41,  46, 105, 110, 110, 101, 114,  84, 101, 120, 116, // ').innerText
  32,  61,  32, 114,  59,  32, 125,  41,  10,  32,  32,  32, //  = r; }).   
  32,  32,  32,  46, 116, 104, 101, 110,  40, 114,  32,  61, //    .then(r =
  62,  32, 102, 101, 116,  99, 104,  40,  39,  47,  97, 112, // > fetch('/ap
 105,  47, 108, 111, 103,  47, 108, 105, 118, 101,  39,  41, // i/log/live')
  41,  10,  32,  32,  32,  32,  32,  32,  46, 116, 104, 101, // ).      .the
 110,  40, 114,  32,  61,  62,  32, 114,  46,  98, 111, 100, // n(r => r.bod
 121,  46, 103, 101, 116,  82, 101,  97, 100, 101, 114,  40, // y.getReader(
  41,  41,  10,  32,  32,  32,  32,  32,  32,  46, 116, 104, // )).      .th
 101, 110,  40, 102,  41,  59,  10,  32,  32,  60,  47, 115, // en(f);.  </s
  99, 114, 105, 112, 116,  62,  10,  60,  47, 104, 116, 109, // cript>.</htm
 108,  62,  10, 0 // l>.
};
static const unsigned char v2[] = {
 109, 103,  95, 109, 105, 108, 108, 105, 115,  32, 105, 115, // mg_millis is
  58,  32,  49,  55,  52,  53,  49,  48,  10, 109, 103,  95, // : 174510.mg_
 109, 105, 108, 108, 105, 115,  32, 105, 115,  58,  32,  49, // millis is: 1
  55,  53,  53,  49,  50,  10, 109, 103,  95, 109, 105, 108, // 75512.mg_mil
 108, 105, 115,  32, 105, 115,  58,  32,  49,  55,  54,  53, // lis is: 1765
  49,  54,  10, 109, 103,  95, 109, 105, 108, 108, 105, 115, // 16.mg_millis
  32, 105, 115,  58,  32,  49,  55,  55,  53,  49,  56,  10, //  is: 177518.
  10, 0 // .
};

static const struct packed_file {
  const char *name;
  const unsigned char *data;
  size_t size;
  time_t mtime;
} packed_files[] = {
  {"/web_root/index.html", v1, sizeof(v1), 1701234907},
  {"/web_root/log.txt", v2, sizeof(v2), 1701234907},
  {NULL, NULL, 0, 0}
};

static int scmp(const char *a, const char *b) {
  while (*a && (*a == *b)) a++, b++;
  return *(const unsigned char *) a - *(const unsigned char *) b;
}
const char *mg_unlist(size_t no) {
  return packed_files[no].name;
}
const char *mg_unpack(const char *name, size_t *size, time_t *mtime) {
  const struct packed_file *p;
  for (p = packed_files; p->name != NULL; p++) {
    if (scmp(p->name, name) != 0) continue;
    if (size != NULL) *size = p->size - 1;
    if (mtime != NULL) *mtime = p->mtime;
    return (const char *) p->data;
  }
  return NULL;
}