use std::str::FromStr;
use std::io::stdin;
const RAW: [&'static str; 7] = [
    "(11/(45-1)*4)",                     // 2^0=1
    "(-11+4-5+14)",                      // 2^1=2
    "(-11-4+5+14)",                      // 2^2=4
    "(11-4-5+14)",                       // 2^4=16
    "((114-51)*4+(-11-4+5+14))",         // 2^8=256
    "(114*514+(11*45*14+(-11/4+51/4)))", // 2^16=65536
    "(114514*(114*51*4+(11451+4+(114*(5+1)*4+(114-51-4))))+(11*(451+4)+(-1+1*4*51+4)))", // 2^32=4294967296
];
fn homo_binary(mut exp: u32) {
    if exp == 0 {
        print!("{}", RAW[0]);
    }
    let mut s = false;
    let mut tmp: u32;
    while exp != 0 {
        tmp = exp.trailing_zeros();
        if s {
            print!("*")
        }
        s = true;
        print!("{}", RAW[(tmp + 1) as usize]);
        exp ^= 1 << tmp;
    }
}
fn homo(mut num: u64) {
    if num == 0 {
        print!("(1-1)*514");
    }
    let mut s = false;
    let mut tmp: u32;
    while num != 0 {
        tmp = num.trailing_zeros();
        if s {
            print!("+")
        }
        s = true;
        homo_binary(tmp);
        num ^= 1 << tmp;
    }
}
fn main() {
    let mut input = String::new();
    stdin().read_line(&mut input).expect("failed to read line");
    let int = u64::from_str(&input.trim()).expect("not a valid input");
    print!("{}=", int);
    homo(int);
}
