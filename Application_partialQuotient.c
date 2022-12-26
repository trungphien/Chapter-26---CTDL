
/*ỨNG DỤNG THUẬT TOÁN XÁC ĐỊNH THƯƠNG SỐ TỪNG PHẦN TRONG PHỤC HỒI SỐ HỮU TỶ

*ĐẶT VẤN ĐỀ:
Một vị giáo sư toán - tin rất cẩn thận nhưng đãng trí. Cách đây vài hôm ngân hàng gửi ông một bức thư thông báo mật khẩu của thẻ tín dụng.Mật khẩu là một số có 6 chữ số: abcdef. Ông không muốn
giữ bức thư vì sợ nó rơi vào tay kẻ gian. Vì vậy ông đã dùng 1 chiếc máy tính xách tay đơn giản để tính tỉ số abc : def. Ông đã nhận được kết và gần đúng là 0.195323246 và ghi nhớ lại lên một tờ giấy.
Làm thế nào để vị giáo sư có thể tìm lại được mật khẩu trong thời gian ngắn nhất nếu ông chỉ có trong tay chiếc máy tính xách tay đơn giản và mật khẩu là gì?

*HƯỚNG GIẢI QUYẾT:
Khai triển số x = 0.195323246 thành dạng liên phân số (phân số liên tục) x = [a0 : a1, a2,...].
Nếu đặt xn = [a0 : a1, a2,..., an] là liên phân số dùng n số hạng đầu tiên của liên phân số x = [a0 : a1, a2,...].
Ta sẽ thấy xn là xấp xỉ của x và n càng lớn thì xn càng có giá trị gần x.
Ở đây ta sẽ ứng dụng thuật toán xác định thương số từng phần để tìm ra các liên phân số xn, sau đó đối chiếu xn với yêu cầu bài toán và đưa ra kết quả.
*/
#include<stdlib.h>
#include<gmp.h>
#define mpf_for(buf, op, n)\
    do {\
        size_t i;\
        for (i = 0; i < (n); ++i)\
            mpf_##op(buf[i]);\
    } while (0)
#define n 10000
int main()
{
    mpf_set_default_prec(2048);
    mpf_t *a = malloc(sizeof(mpf_t) * (n + 1));
    mpf_for(a, init, n + 1);

    mpz_t num, d;
    mpq_t tempq, tempq1;
    mpf_t s, r, S, R, y, temp, temp1, luythua;

    mpz_inits(num, d, NULL);
    mpq_inits(tempq, tempq1, NULL);
    mpf_inits(s, r, S, R, y, temp, temp1, luythua, NULL);

    mpf_set_ui(luythua, 10);
    mpf_pow_ui(luythua, luythua, 30);

    mpf_set_str(y, "0.195323246", 10);
    mpf_set_str(r, "0.1953232459999999999999999999999999999999999", 10);
    mpf_set_str(s, "0.1953232460000000000000000000000000000000001", 10);
    // r <= y <= s

    mpf_trunc(S, s);
    mpf_trunc(R, r);

    int i=0;
    while(mpf_cmp(S, R) == 0)
    {
        // a[i] = [y];
        mpf_trunc(a[i], y);
        mpf_sub(y, y, a[i]);
        mpf_ui_div(y, 1, y);

        mpf_sub(s, s, S);
        mpf_sub(r, r, R);

        mpf_ui_div(temp, 1, s);
        mpf_ui_div(temp1, 1, r);

        mpf_mul(temp, temp, luythua);
        mpf_trunc(temp, temp);
        mpf_div(temp, temp, luythua);

        mpf_mul(temp1, temp1, luythua);
        mpf_ceil(temp1, temp1);
        mpf_div(temp1, temp1, luythua);

        mpf_set(r, temp);
        mpf_set(s, temp1);
        mpf_trunc(S, s);
        mpf_trunc(R, r);
        i++;
    }

    int j, k;
    gmp_printf("%d thuong so tung phan xac dinh duoc la: \n", i);
    for(j = 0; j<i; j++)
    {
         gmp_printf("a[%u] = %.Ff\n",j,  a[j]);
    }

    gmp_printf("_______________________________________________\n");
    for(j = i-1; j>=0; j--)
    {
         gmp_printf("x[%u] = ", j);
         mpq_set_f(tempq, a[j]);
         for(k = j-1; k>=0; k--)
         {
            mpq_set_ui(tempq1, 1, 1);
            mpq_div(tempq, tempq1, tempq);
            mpq_set_f(tempq1, a[k]);
            mpq_add(tempq, tempq, tempq1);

         }
         mpq_get_num(num, tempq);
         mpq_get_den(d,tempq);
         gmp_printf("%Zd / %Zd\n", num, d);
         if(mpz_cmp_ui(num, 100) >= 0 && mpz_cmp_ui(num, 999) <= 0 && mpz_cmp_ui(d, 100) >= 0 && mpz_cmp_ui(d, 999) <= 0)
         {
             gmp_printf("_______________________________________________\n");
             gmp_printf("abc = numerator = %Zd\n", num);
             gmp_printf("def = denominator = %Zd\n", d);
             mpz_mul_ui(num, num, 1000);
             mpz_add(num, num, d);
             gmp_printf("--> Mat khau can tim la: %Zd", num);
             gmp_printf("\n_______________________________________________\n");
             break;
         }
    }

    mpz_clears(num, d, NULL);
    mpq_clears(tempq, tempq1, NULL);
    mpf_clears(s, r, S, R, y, temp, temp1, luythua, NULL);
    mpf_for(a, clear, n + 1);
    free(a);
}
