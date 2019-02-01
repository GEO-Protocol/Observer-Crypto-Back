#include "file_generator.h"

    file_generator::file_generator()
    {
        sodium_init();
        add_claim();
        read_claim();
        make_buffer();
        add_stack();
    }

    void file_generator::add_claim()
    {
        std::ofstream writeFILE("data.txt", std::ios::binary);
        writeFILE.write((char*)&block_number, sizeof(block_number));
        writeFILE.write((char*)&block_uuid, sizeof(block_uuid));
        writeFILE.write((char*)&user_amount, sizeof(user_amount));

        for(uint16_t i = 0;i < user_amount;)
        {

            PrivateKey *pKey = new PrivateKey();

            private_keys.push_back(pKey);

            auto pubKey = pKey->derivePublicKey()->data();
            writeFILE.write((char*)&i, sizeof(uint16_t));
            writeFILE.write((char*)pubKey, PublicKey::kKeySize());

            ++i;

        }
        writeFILE.close();
    };

    void file_generator::read_claim()
    {
        std::ifstream readFILE("data.txt", std::ios::binary);

        readFILE.read((char*)&get_block, sizeof(uint64_t));
        readFILE.seekg(sizeof(uint64_t));
        readFILE.read((char*)&get_block_uuid, sizeof(get_block_uuid));
        readFILE.read((char*)&get_user_amount, sizeof(get_user_amount));

        for(int i = 0; i < get_user_amount;){

            uint16_t id;
            readFILE.read((char*)&id, sizeof(uint16_t));
            ids.push_back(id);
            readFILE.seekg(PublicKey::kKeySize(), readFILE.cur);
            i++;
        }
        readFILE.close();
    };

    void file_generator::make_buffer()
    {
        std::ofstream writeFILE("buffer_reference_data.txt", std::ios::binary);
        writeFILE.write((char*)&get_block, sizeof(get_block));
        writeFILE.write((char*)&get_block_uuid, sizeof(get_block_uuid));
        writeFILE.write((char*)&get_user_amount, sizeof(get_user_amount));

        for(int i = 0; i < get_user_amount;)
        {
            writeFILE.write((char*)&ids[i], sizeof(uint16_t));
            i++;
        }

        writeFILE.close();
        //byte *buffer_reference_data = new byte[sizeof(uint16_t)+ sizeof(uint16_t)+sizeof(boost::uuids::uuid)+(sizeof(uint16_t)*get_user_amount)];

        std::ifstream readFIle("buffer_reference_data.txt", std::ios::binary);

        readFIle.read((char*)buffer, sizeof(buffer));

        readFIle.close();
        remove("buffer_reference_data.txt");
    };

    void file_generator::add_stack()
    {
        std::ofstream writeFILE("data.txt", std::ios::app );
        writeFILE.write((char*)&block_number, sizeof(block_number));
        writeFILE.write((char*)&block_uuid, sizeof(block_uuid));
        writeFILE.write((char*)&user_amount, sizeof(user_amount));

        for(uint16_t i = 0;i < user_amount;)
        {

            Signature sig(buffer, sizeof(buffer), private_keys[i]);
            auto signaturo = sig.data();

            writeFILE.write((char*)&i, sizeof(uint16_t));
            writeFILE.write((char*)signaturo, Signature::signatureSize());

            ++i;
        }
        writeFILE.close();
    };


