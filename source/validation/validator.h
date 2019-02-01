#ifndef OCB_VALIDATOR_H
#define OCB_VALIDATOR_H

#include "../../include/includes.h"

class validator
{
public:
    explicit validator(const char* file_name);
    void read_claim(ifstream& infile);
    void read_stack(ifstream& infile);
    void make_buffer();
    void validation();
private:
    uint64_t claim_block_number, stack_block_number;
    uint16_t claim_user_amount, stack_user_amount;
    uint16_t ID;
    std::vector<uint16_t> paymentID;
    boost::uuids::uuid claim_uuid, stack_uuid;
    std::vector<byte*>publicKeys, signatures;
    byte *buffer_signature = new byte[Signature::signatureSize()];
    byte* buffer_public_keys = new byte[PublicKey::kKeySize()];
    byte *buffer_reference_data = new byte[sizeof(uint16_t)+ sizeof(uint16_t)+sizeof(boost::uuids::uuid)+(sizeof(uint16_t)*claim_user_amount)];

};
#endif //OCB_VALIDATOR_H
