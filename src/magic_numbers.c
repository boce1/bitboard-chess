#include "magic_numbers.h"
// #include "bitboard.h"
// #include <stdio.h>
// #include <string.h>
// #include <inttypes.h>

const uint64_t rook_magic_numbers[64] = {
    9979994641325359136ULL,
    90072129987412032ULL,
    180170925814149121ULL,
    72066458867205152ULL,
    144117387368072224ULL,
    216203568472981512ULL,
    9547631759814820096ULL,
    2341881152152807680ULL,
    140740040605696ULL,
    2316046545841029184ULL,
    72198468973629440ULL,
    81205565149155328ULL,
    146508277415412736ULL,
    703833479054336ULL,
    2450098939073003648ULL,
    576742228899270912ULL,
    36033470048378880ULL,
    72198881818984448ULL,
    1301692025185255936ULL,
    90217678106527746ULL,
    324684134750365696ULL,
    9265030608319430912ULL,
    4616194016369772546ULL,
    2199165886724ULL,
    72127964931719168ULL,
    2323857549994496000ULL,
    9323886521876609ULL,
    9024793588793472ULL,
    562992905192464ULL,
    2201179128832ULL,
    36038160048718082ULL,
    36029097666947201ULL,
    4629700967774814240ULL,
    306244980821723137ULL,
    1161084564161792ULL,
    110340390163316992ULL,
    5770254227613696ULL,
    2341876206435041792ULL,
    82199497949581313ULL,
    144120019947619460ULL,
    324329544062894112ULL,
    1152994210081882112ULL,
    13545987550281792ULL,
    17592739758089ULL,
    2306414759556218884ULL,
    144678687852232706ULL,
    9009398345171200ULL,
    2326183975409811457ULL,
    72339215047754240ULL,
    18155273440989312ULL,
    4613959945983951104ULL,
    145812974690501120ULL,
    281543763820800ULL,
    147495088967385216ULL,
    2969386217113789440ULL,
    19215066297569792ULL,
    180144054896435457ULL,
    2377928092116066437ULL,
    9277424307650174977ULL,
    4621827982418248737ULL,
    563158798583922ULL,
    5066618438763522ULL,
    144221860300195844ULL,
    281752018887682ULL
};

const uint64_t bishop_magic_numbers[64] = {
    18018831494946945ULL,
    1134767471886336ULL,
    2308095375972630592ULL,
    27308574661148680ULL,
    9404081239914275072ULL,
    4683886618770800641ULL,
    216245358743802048ULL,
    9571253153235970ULL,
    27092002521253381ULL,
    1742811846410792ULL,
    8830470070272ULL,
    9235202921558442240ULL,
    1756410529322199040ULL,
    1127005325142032ULL,
    1152928124311179269ULL,
    2377913937382869017ULL,
    2314850493043704320ULL,
    4684324174200832257ULL,
    77688339246880000ULL,
    74309421802472544ULL,
    8649444578941734912ULL,
    4758897525753456914ULL,
    18168888584831744ULL,
    2463750540959940880ULL,
    9227893366251856128ULL,
    145276341141897348ULL,
    292821938185734161ULL,
    5190965918678714400ULL,
    2419567834477633538ULL,
    2308272929927873024ULL,
    18173279030480900ULL,
    612771170333492228ULL,
    4611976426970161409ULL,
    2270508834359424ULL,
    9223442681551127040ULL,
    144117389281722496ULL,
    1262208579542270208ULL,
    13988180992906560530ULL,
    4649975687305298176ULL,
    9809420809726464128ULL,
    1153222256471056394ULL,
    2901448468860109312ULL,
    40690797321924624ULL,
    4504295814726656ULL,
    299204874469892ULL,
    594838215186186752ULL,
    7210408796106130432ULL,
    144405467744964672ULL,
    145390656058359810ULL,
    1153203537948246016ULL,
    102002796048417802ULL,
    9243919728426124800ULL,
    2455024885924167748ULL,
    72066815467061280ULL,
    325424741529814049ULL,
    1175584649085829253ULL,
    18720594346444812ULL,
    584352516473913920ULL,
    1441151883179198496ULL,
    4919056693802862608ULL,
    1161950831810052608ULL,
    2464735771073020416ULL,
    54610562058947072ULL,
    580611413180448ULL
};

/*
    FUNCTIONS BELLOW ARE ONLY RAN ONCE, 
    FOR PURPOUSE BEING GENERATING MAGIC NUMBERS.
    The idia is not generating them every time the program starts.
*/

/*
unsigned int random_state = 1804289383; // initial random state, IDIA IS MAKING THE ENGINE CROSS PLATFORM

unsigned int get_random_uint_32() {
    unsigned int x = random_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    random_state = x;
    return x;
}

uint64_t get_random_uint64_t() {
    uint64_t n1, n2, n3, n4;
    n1 = (uint64_t)(get_random_uint_32()) & 0xFFFF;
    n2 = (uint64_t)(get_random_uint_32()) & 0xFFFF;
    n3 = (uint64_t)(get_random_uint_32()) & 0xFFFF;
    n4 = (uint64_t)(get_random_uint_32()) & 0xFFFF;

    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

uint64_t generate_magic_number() {
    return get_random_uint64_t() & get_random_uint64_t() & get_random_uint64_t();
}

uint64_t find_magic_number(int square, int relevant_bits, int piece_type, leaper_moves_masks* masks) {
    uint64_t occupancies[4096];
    uint64_t attacks[4096];
    uint64_t used_attacks[4096];
    uint64_t attack_mask = (piece_type == rook) ? masks->rook[square] : masks->bishop[square];

    int num_permutations = 1 << relevant_bits;
    for(int index = 0; index < num_permutations; index++) {
        occupancies[index] = get_occupancy_permutation(index, relevant_bits, attack_mask);
        if (piece_type == rook) {
            attacks[index] = rook_attacks_on_the_fly(square, occupancies[index]);
        } else {
            attacks[index] = bishop_attacks_on_the_fly(square, occupancies[index]);
        }
    }

    int index, fail;
    for(int random_count = 0; random_count < 100000000; random_count++) {
        uint64_t magic_number = generate_magic_number();
        if(count_bits((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;
        memset(used_attacks, 0ULL, sizeof(used_attacks));

        for(index = 0, fail = 0; !fail && index < num_permutations; index++) {
            int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));

            if(used_attacks[magic_index] == 0ULL) {
                used_attacks[magic_index] = attacks[index];
            } else if(used_attacks[magic_index] != attacks[index]) {
                fail = 1;
            }
        }
        if(!fail) return magic_number;
    }
    printf("Failed to find magic number for square %d with %d relevant bits\n", square, relevant_bits);
    return 0ULL;
}

void print_magic_numbers(int piece_type, leaper_moves_masks* masks) {
    for(int square = 0; square < 64; square++) {
        int relevant_bits = (piece_type == rook) ? rook_relevant_bits[square] : bishop_relevant_bits[square];
        uint64_t magic_number = find_magic_number(square, relevant_bits, piece_type, masks);
        printf("    %" PRIu64 "ULL,\n", magic_number);
        
    } 

}
*/