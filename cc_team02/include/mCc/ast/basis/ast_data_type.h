#ifndef MCC_AST_DATA_TYPE_H
#define MCC_AST_DATA_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_ast_data_type {
	// use void only for functions!
	MCC_AST_DATA_TYPE_VOID,
	MCC_AST_DATA_TYPE_INT,
	MCC_AST_DATA_TYPE_FLOAT,
	MCC_AST_DATA_TYPE_BOOL,
	MCC_AST_DATA_TYPE_STRING,
	//added for semantic checks if binary-op reports different type!
	/*TODO: add this case to all switches!*/
	MCC_AST_DATA_TYPE_INCONSISTENT,
	//needed if unknown identifier was processed
	MCC_AST_DATA_TYPE_UNKNOWN
};

#ifdef __cplusplus
}
#endif

#endif
