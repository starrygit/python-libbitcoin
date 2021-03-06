typedef struct bc_chain_state_t bc_chain_state_t;
typedef struct bc_data_chunk_t bc_data_chunk_t;
typedef struct bc_error_code_t bc_error_code_t;
typedef struct bc_hash_digest_t bc_hash_digest_t;
typedef struct bc_input_list_t bc_input_list_t;
typedef struct bc_output_list_t bc_output_list_t;
typedef struct bc_point_indexes_t bc_point_indexes_t;
typedef struct bc_script_t bc_script_t;
typedef struct bc_string_t bc_string_t;

typedef struct bc_transaction_t bc_transaction_t;

// Constructor
bc_transaction_t* bc_create_transaction();
bc_transaction_t* bc_create_transaction_copy(const bc_transaction_t* other);
bc_transaction_t* bc_create_transaction_copy_Hash(
    const bc_transaction_t* other, const bc_hash_digest_t* hash);
bc_transaction_t* bc_create_transaction_Parts(
    uint32_t version, uint32_t locktime,
    const bc_input_list_t* inputs, const bc_output_list_t* outputs);

// Destructor
void bc_destroy_transaction(bc_transaction_t* self);

// Operators.
void bc_transaction__copy(
    bc_transaction_t* self, const bc_transaction_t* other);

bool bc_transaction__equals(
    const bc_transaction_t* self, const bc_transaction_t* other);
bool bc_transaction__not_equals(
    const bc_transaction_t* self, const bc_transaction_t* other);

// Deserialization.
bc_transaction_t* bc_transaction__factory_from_data(
    const bc_data_chunk_t* data);
bc_transaction_t* bc_transaction__factory_from_data_nowire(
    const bc_data_chunk_t* data);

bool bc_transaction__from_data(bc_transaction_t* self,
    const bc_data_chunk_t* data);
bool bc_transaction__from_data_nowire(bc_transaction_t* self,
    const bc_data_chunk_t* data);

bool bc_transaction__is_valid(const bc_transaction_t* self);

// Serialization.
bc_data_chunk_t* bc_transaction__to_data(const bc_transaction_t* self);
bc_data_chunk_t* bc_transaction__to_data_nowire(
    const bc_transaction_t* self);

// Properties (size, accessors, cache).
uint64_t bc_transaction__serialized_size(const bc_transaction_t* self);
uint64_t bc_transaction__serialized_size_nowire(const bc_transaction_t* self);

uint32_t bc_transaction__version(const bc_transaction_t* self);
void bc_transaction__set_version(bc_transaction_t* self, uint32_t version);

uint32_t bc_transaction__locktime(const bc_transaction_t* self);
void bc_transaction__set_locktime(bc_transaction_t* self, uint32_t locktime);

bc_input_list_t* bc_transaction__inputs(const bc_transaction_t* self);
void bc_transaction__set_inputs(bc_transaction_t* self,
    const bc_input_list_t* inputs);

bc_output_list_t* bc_transaction__outputs(const bc_transaction_t* self);
void bc_transaction__set_outputs(bc_transaction_t* self,
    const bc_output_list_t* outputs);

bc_hash_digest_t* bc_transaction__hash(const bc_transaction_t* self);
bc_hash_digest_t* bc_transaction__hash_Sighash(const bc_transaction_t* self,
    uint32_t sighash_type);

// Validation.
uint64_t bc_transaction__fees(const bc_transaction_t* self);
/*bc_point_indexes_t* bc_transaction__double_spends(
    const bc_transaction_t* self, bool include_unconfirmed);
bc_point_indexes_t* bc_transaction__immature_inputs(
    const bc_transaction_t* self, size_t target_height);*/
bc_point_indexes_t* bc_transaction__missing_previous_outputs(
    const bc_transaction_t* self);
uint64_t bc_transaction__total_input_value(const bc_transaction_t* self);
uint64_t bc_transaction__total_output_value(const bc_transaction_t* self);
size_t bc_transaction__signature_operations(
    const bc_transaction_t* self, bool bip16_active);

bool bc_transaction__is_coinbase(const bc_transaction_t* self);
bool bc_transaction__is_null_non_coinbase(const bc_transaction_t* self);
bool bc_transaction__is_oversized_coinbase(const bc_transaction_t* self);
bool bc_transaction__is_immature(const bc_transaction_t* self,
    size_t target_height);
bool bc_transaction__is_overspent(const bc_transaction_t* self);
bool bc_transaction__is_double_spend(const bc_transaction_t* self,
    bool include_unconfirmed);
bool bc_transaction__is_missing_previous_outputs(const bc_transaction_t* self);
bool bc_transaction__is_final(const bc_transaction_t* self,
    uint64_t block_height, uint32_t block_time);
bool bc_transaction__is_locktime_conflict(const bc_transaction_t* self);

bc_error_code_t* bc_transaction__check(const bc_transaction_t* self);
bc_error_code_t* bc_transaction__check_notransaction_pool(
    const bc_transaction_t* self);
bc_error_code_t* bc_transaction__accept(
    const bc_transaction_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_transaction__accept_notransaction_pool(
    const bc_transaction_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_transaction__connect(
    const bc_transaction_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_transaction__connect_input(
    const bc_transaction_t* self, const bc_chain_state_t* state,
    uint32_t input_index);

