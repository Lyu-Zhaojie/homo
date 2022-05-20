const raw_data: string[] = [
    "(11/(45-1)*4)",                                                                    // 2^0=1
    "(-11+4-5+14)",                                                                     // 2^1=2
    "(-11-4+5+14)",                                                                     // 2^2=4
    "(11-4-5+14)",                                                                      // 2^4=16
    "((114-51)*4+(-11-4+5+14))",                                                        // 2^8=256
    "(114*514+(11*45*14+(-11/4+51/4)))",                                                // 2^16=65536
    "(114514*(114*51*4+(11451+4+(114*(5+1)*4+(114-51-4))))+(11*(451+4)+(-1+1*4*51+4)))" // 2^32=4294967296
];
function homoBinary(exp: number): string {
    if (exp === 0)
        return raw_data[0];
    let str: string = exp.toString(2);
    let flag: boolean = false;
    let ans: string = "";
    for (let i = str.length - 1; i >= 0; i--) {
        if (str[i] === '1') {
            if (flag)
                ans += '*';
            flag = true;
            ans += raw_data[str.length - i];
        }
    }
    return ans;
}
function homoNum(num: number): string {
    if (num === 0)
        return "(1-1)*4514";
    if (num < 0)
        return "(11-4-5+1-4)*" + homoNum(-num);
    let str: string = num.toString(2);
    let flag: boolean = false;
    let ans: string = "";
    for (let i = str.length - 1; i >= 0; i--) {
        if (str[i] === '1') {
            if (flag)
                ans += '+';
            flag = true;
            ans += homoBinary(str.length - 1 - i);
        }
    }
    return ans;
}
function homo(num: string): string {
    const rule: RegExp = new RegExp("-?[1-9][0-9]*");
    if (!rule.test(num))
        return "太差太差的" + num + "有论证的必要吗";
    return "=" + homoNum(parseInt(num, 10));
}
let num: string = "-114514";
console.log(homo(num));
