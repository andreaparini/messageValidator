// See README.txt for information and build instructions.


#include "test.h"
#include "../proto/test1.pb.h"
#include "../proto/test2.pb.h"

using namespace std;

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;
using google::protobuf::Message;

using google::protobuf::DoubleValue;
using google::protobuf::Int32Value;
using google::protobuf::Int64Value;
using google::protobuf::UInt32Value;
using google::protobuf::UInt64Value;


bool testMessage(const Message& message, 
                 const Validator::ValidationOutput expected) {
    Validator v;
    vector<Validator::ValidationOutput> computed = v.validate(message);
    for (int k = 0; k < computed.size(); k++) {    
        if (computed[k] != expected) {
            return false;
        }
    } 
    return true;
};

bool test1_validation () {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    int testsPassed = 0;
    
    
    /*
     *   DOUBLE
     */
    
    
    // Double Equal
    test1::DoubleEqual doubleEqual;  
    DoubleValue* doubleEqualWrapper = doubleEqual.mutable_val();  
    double doubleEqualTrue    = 5.;
    doubleEqualWrapper->set_value(doubleEqualTrue);  
    if (testMessage(doubleEqual, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: DoubleEqualTrue" << endl;
    
    double doubleEqualFalse   = 4.;
    doubleEqualWrapper->set_value(doubleEqualFalse);  
    if (testMessage(doubleEqual, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: DoubleEqualFalse" << endl;
    
    // Double Lt
    test1::DoubleLt doubleLt;  
    DoubleValue* doubleLtWrapper = doubleLt.mutable_val();  
    double doubleLtTrue    = 4.;
    doubleLtWrapper->set_value(doubleLtTrue);  
    if (testMessage(doubleLt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: DoubleLtTrue" << endl;
    
    double doubleLtFalse   = 6.;
    doubleLtWrapper->set_value(doubleLtFalse);  
    if (testMessage(doubleLt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: DoubleLtFalse" << endl;
    
    // Double Lte
    test1::DoubleLte doubleLte;  
    DoubleValue* doubleLteWrapper = doubleLte.mutable_val();  
    double doubleLteTrue    = 5.;
    doubleLteWrapper->set_value(doubleLteTrue);  
    if (testMessage(doubleLte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: DoubleLteTrue" << endl;
    
    double doubleLteFalse   = 6.;
    doubleLteWrapper->set_value(doubleLteFalse);  
    if (testMessage(doubleLte, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: DoubleLteFalse" << endl;
    
    // Double Lte2
    test1::DoubleLte2 doubleLte2;  
    DoubleValue* doubleLte2Wrapper = doubleLte2.mutable_val();  
    double doubleLte2True    = 4.;
    doubleLte2Wrapper->set_value(doubleLte2True);  
    if (testMessage(doubleLte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: DoubleLte2True" << endl;
    
    double doubleLte2False   = 6.;
    doubleLte2Wrapper->set_value(doubleLte2False);  
    if (testMessage(doubleLte2, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: DoubleLte2False" << endl;
    
    // Double Gt
    test1::DoubleGt doubleGt;  
    DoubleValue* doubleGtWrapper = doubleGt.mutable_val();  
    double doubleGtTrue    = 6.;
    doubleGtWrapper->set_value(doubleGtTrue);  
    if (testMessage(doubleGt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: DoubleGtTrue" << endl;
    
    double doubleGtFalse   = 4.;
    doubleGtWrapper->set_value(doubleGtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: DoubleGtFalse" << endl;
    
    // Double Gte
    test1::DoubleGte doubleGte;  
    DoubleValue* doubleGteWrapper = doubleGte.mutable_val();  
    double doubleGteTrue    = 5.;
    doubleGteWrapper->set_value(doubleGteTrue);  
    if (testMessage(doubleGte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: DoubleGteTrue" << endl;
    
    double doubleGteFalse   = 4.;
    doubleGteWrapper->set_value(doubleGteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: DoubleGteFalse" << endl;
    
    // Double Gte2
    test1::DoubleGte2 doubleGte2;  
    DoubleValue* doubleGte2Wrapper = doubleGte2.mutable_val();  
    double doubleGte2True    = 6.;
    doubleGte2Wrapper->set_value(doubleGte2True);  
    if (testMessage(doubleGte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: DoubleGte2True" << endl;
    
    double doubleGte2False   = 4.;
    doubleGte2Wrapper->set_value(doubleGte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: DoubleGte2False" << endl;
    
    /*
     *   INT32
     */
    
    
    // Int32 Equal
    test1::Int32Equal int32Equal;  
    Int32Value* int32EqualWrapper = int32Equal.mutable_val();  
    int32_t int32EqualTrue    = 5.;
    int32EqualWrapper->set_value(int32EqualTrue);  
    if (testMessage(int32Equal, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int32EqualTrue" << endl;
    
    int32_t int32EqualFalse   = 4.;
    int32EqualWrapper->set_value(int32EqualFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int32EqualFalse" << endl;
    
    // Int32 Lt
    test1::Int32Lt int32Lt;  
    Int32Value* int32LtWrapper = int32Lt.mutable_val();  
    int32_t int32LtTrue    = 4.;
    int32LtWrapper->set_value(int32LtTrue);  
    if (testMessage(int32Lt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int32LtTrue" << endl;
    
    int32_t int32LtFalse   = 6.;
    int32LtWrapper->set_value(int32LtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int32LtFalse" << endl;
    
    // Int32 Lte
    test1::Int32Lte int32Lte;  
    Int32Value* int32LteWrapper = int32Lte.mutable_val();  
    int32_t int32LteTrue    = 5.;
    int32LteWrapper->set_value(int32LteTrue);  
    if (testMessage(int32Lte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int32LteTrue" << endl;
    
    int32_t int32LteFalse   = 6.;
    int32LteWrapper->set_value(int32LteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int32LteFalse" << endl;
    
    // Int32 Lte2
    test1::Int32Lte2 int32Lte2;  
    Int32Value* int32Lte2Wrapper = int32Lte2.mutable_val();  
    int32_t int32Lte2True    = 4.;
    int32Lte2Wrapper->set_value(int32Lte2True);  
    if (testMessage(int32Lte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int32Lte2True" << endl;
    
    int32_t int32Lte2False   = 6.;
    int32Lte2Wrapper->set_value(int32Lte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int32Lte2False" << endl;
    
    // Int32 Gt
    test1::Int32Gt int32Gt;  
    Int32Value* int32GtWrapper = int32Gt.mutable_val();  
    int32_t int32GtTrue    = 6.;
    int32GtWrapper->set_value(int32GtTrue);  
    if (testMessage(int32Gt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int32GtTrue" << endl;
    
    int32_t int32GtFalse   = 4.;
    int32GtWrapper->set_value(int32GtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int32GtFalse" << endl;
    
    // Int32 Gte
    test1::Int32Gte int32Gte;  
    Int32Value* int32GteWrapper = int32Gte.mutable_val();  
    int32_t int32GteTrue    = 5.;
    int32GteWrapper->set_value(int32GteTrue);  
    if (testMessage(int32Gte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int32GteTrue" << endl;
    
    int32_t int32GteFalse   = 4.;
    int32GteWrapper->set_value(int32GteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int32GteFalse" << endl;
    
    // Int32 Gte2
    test1::Int32Gte2 int32Gte2;  
    Int32Value* int32Gte2Wrapper = int32Gte2.mutable_val();  
    int32_t int32Gte2True    = 6.;
    int32Gte2Wrapper->set_value(int32Gte2True);  
    if (testMessage(int32Gte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int32Gte2True" << endl;
    
    int32_t int32Gte2False   = 4.;
    int32Gte2Wrapper->set_value(int32Gte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int32Gte2False" << endl;
    
    
    /*
     *   INT64
     */
    
    
    // Int64 Equal
    test1::Int64Equal int64Equal;  
    Int64Value* int64EqualWrapper = int64Equal.mutable_val();  
    int64_t int64EqualTrue    = 5.;
    int64EqualWrapper->set_value(int64EqualTrue);  
    if (testMessage(int64Equal, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int64EqualTrue" << endl;
    
    int64_t int64EqualFalse   = 4.;
    int64EqualWrapper->set_value(int64EqualFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
          testsPassed++;
    else 
        cout << "FAILED: Int64EqualFalse" << endl;
    
    // Int64 Lt
    test1::Int64Lt int64Lt;  
    Int64Value* int64LtWrapper = int64Lt.mutable_val();  
    int64_t int64LtTrue    = 4.;
    int64LtWrapper->set_value(int64LtTrue);  
    if (testMessage(int64Lt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int64LtTrue" << endl;
    
    int64_t int64LtFalse   = 6.;
    int64LtWrapper->set_value(int64LtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int64LtFalse" << endl;
    
    // Int64 Lte
    test1::Int64Lte int64Lte;  
    Int64Value* int64LteWrapper = int64Lte.mutable_val();  
    int64_t int64LteTrue    = 5.;
    int64LteWrapper->set_value(int64LteTrue);  
    if (testMessage(int64Lte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int64LteTrue" << endl;
    
    int64_t int64LteFalse   = 6.;
    int64LteWrapper->set_value(int64LteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int64LteFalse" << endl;
    
    // Int64 Lte2
    test1::Int64Lte2 int64Lte2;  
    Int64Value* int64Lte2Wrapper = int64Lte2.mutable_val();  
    int64_t int64Lte2True    = 4.;
    int64Lte2Wrapper->set_value(int64Lte2True);  
    if (testMessage(int64Lte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int64Lte2True" << endl;
    
    int64_t int64Lte2False   = 6.;
    int64Lte2Wrapper->set_value(int64Lte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int64Lte2False" << endl;
    
    // Int64 Gt
    test1::Int64Gt int64Gt;  
    Int64Value* int64GtWrapper = int64Gt.mutable_val();  
    int64_t int64GtTrue    = 6.;
    int64GtWrapper->set_value(int64GtTrue);  
    if (testMessage(int64Gt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int64GtTrue" << endl;
    
    int64_t int64GtFalse   = 4.;
    int64GtWrapper->set_value(int64GtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int64GtFalse" << endl;
    
    // Int64 Gte
    test1::Int64Gte int64Gte;  
    Int64Value* int64GteWrapper = int64Gte.mutable_val();  
    int64_t int64GteTrue    = 5.;
    int64GteWrapper->set_value(int64GteTrue);  
    if (testMessage(int64Gte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int64GteTrue" << endl;
    
    int64_t int64GteFalse   = 4.;
    int64GteWrapper->set_value(int64GteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int64GteFalse" << endl;
    
    // Int64 Gte2
    test1::Int64Gte2 int64Gte2;  
    Int64Value* int64Gte2Wrapper = int64Gte2.mutable_val();  
    int64_t int64Gte2True    = 6.;
    int64Gte2Wrapper->set_value(int64Gte2True);  
    if (testMessage(int64Gte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: Int64Gte2True" << endl;
    
    int64_t int64Gte2False   = 4.;
    int64Gte2Wrapper->set_value(int64Gte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: Int64Gte2False" << endl;
    
    
    /*
     *   UINT32
     */
    
    
    // UInt32 Equal
    test1::UInt32Equal uint32Equal;  
    UInt32Value* uint32EqualWrapper = uint32Equal.mutable_val();  
    uint32_t uint32EqualTrue    = 5.;
    uint32EqualWrapper->set_value(uint32EqualTrue);  
    if (testMessage(uint32Equal, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt32EqualTrue" << endl;
    
    uint32_t uint32EqualFalse   = 4.;
    uint32EqualWrapper->set_value(uint32EqualFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt32EqualFalse" << endl;
    
    // UInt32 Lt
    test1::UInt32Lt uint32Lt;  
    UInt32Value* uint32LtWrapper = uint32Lt.mutable_val();  
    uint32_t uint32LtTrue    = 4.;
    uint32LtWrapper->set_value(uint32LtTrue);  
    if (testMessage(uint32Lt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt32LtTrue" << endl;
    
    uint32_t uint32LtFalse   = 6.;
    uint32LtWrapper->set_value(uint32LtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt32LtFalse" << endl;
    
    // UInt32 Lte
    test1::UInt32Lte uint32Lte;  
    UInt32Value* uint32LteWrapper = uint32Lte.mutable_val();  
    uint32_t uint32LteTrue    = 5.;
    uint32LteWrapper->set_value(uint32LteTrue);  
    if (testMessage(uint32Lte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt32LteTrue" << endl;
    
    uint32_t uint32LteFalse   = 6.;
    uint32LteWrapper->set_value(uint32LteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt32LteFalse" << endl;
    
    // UInt32 Lte2
    test1::UInt32Lte2 uint32Lte2;  
    UInt32Value* uint32Lte2Wrapper = uint32Lte2.mutable_val();  
    uint32_t uint32Lte2True    = 4.;
    uint32Lte2Wrapper->set_value(uint32Lte2True);  
    if (testMessage(uint32Lte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt32Lte2True" << endl;
    
    uint32_t uint32Lte2False   = 6.;
    uint32Lte2Wrapper->set_value(uint32Lte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
       testsPassed++;
    else 
        cout << "FAILED: UInt32Lte2False" << endl;
    
    // UInt32 Gt
    test1::UInt32Gt uint32Gt;  
    UInt32Value* uint32GtWrapper = uint32Gt.mutable_val();  
    uint32_t uint32GtTrue    = 6.;
    uint32GtWrapper->set_value(uint32GtTrue);  
    if (testMessage(uint32Gt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt32GtTrue" << endl;
    
    uint32_t uint32GtFalse   = 4.;
    uint32GtWrapper->set_value(uint32GtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt32GtFalse" << endl;
    
    // UInt32 Gte
    test1::UInt32Gte uint32Gte;  
    UInt32Value* uint32GteWrapper = uint32Gte.mutable_val();  
    uint32_t uint32GteTrue    = 5.;
    uint32GteWrapper->set_value(uint32GteTrue);  
    if (testMessage(uint32Gte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt32GteTrue" << endl;
    
    uint32_t uint32GteFalse   = 4.;
    uint32GteWrapper->set_value(uint32GteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt32GteFalse" << endl;
    
    // UInt32 Gte2
    test1::UInt32Gte2 uint32Gte2;  
    UInt32Value* uint32Gte2Wrapper = uint32Gte2.mutable_val();  
    uint32_t uint32Gte2True    = 6.;
    uint32Gte2Wrapper->set_value(uint32Gte2True);  
    if (testMessage(uint32Gte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt32Gte2True" << endl;
    
    uint32_t uint32Gte2False   = 4.;
    uint32Gte2Wrapper->set_value(uint32Gte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt32Gte2False" << endl;
    
    
    /*
     *   UINT64
     */
    
    
    // UInt64 Equal
    test1::UInt64Equal uint64Equal;  
    UInt64Value* uint64EqualWrapper = uint64Equal.mutable_val();  
    uint64_t uint64EqualTrue    = 5.;
    uint64EqualWrapper->set_value(uint64EqualTrue);  
    if (testMessage(uint64Equal, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt64EqualTrue" << endl;
    
    uint64_t uint64EqualFalse   = 4.;
    uint64EqualWrapper->set_value(uint64EqualFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt64EqualFalse" << endl;
    
    // UInt64 Lt
    test1::UInt64Lt uint64Lt;  
    UInt64Value* uint64LtWrapper = uint64Lt.mutable_val();  
    uint64_t uint64LtTrue    = 4.;
    uint64LtWrapper->set_value(uint64LtTrue);  
    if (testMessage(uint64Lt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt64LtTrue" << endl;
    
    uint64_t uint64LtFalse   = 6.;
    uint64LtWrapper->set_value(uint64LtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt64LtFalse" << endl;
    
    // UInt64 Lte
    test1::UInt64Lte uint64Lte;  
    UInt64Value* uint64LteWrapper = uint64Lte.mutable_val();  
    uint64_t uint64LteTrue    = 5.;
    uint64LteWrapper->set_value(uint64LteTrue);  
    if (testMessage(uint64Lte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt64LteTrue" << endl;
    
    uint64_t uint64LteFalse   = 6.;
    uint64LteWrapper->set_value(uint64LteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt64LteFalse" << endl;
    
    // UInt64 Lte2
    test1::UInt64Lte2 uint64Lte2;  
    UInt64Value* uint64Lte2Wrapper = uint64Lte2.mutable_val();  
    uint64_t uint64Lte2True    = 4.;
    uint64Lte2Wrapper->set_value(uint64Lte2True);  
    if (testMessage(uint64Lte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt64Lte2True" << endl;
    
    uint64_t uint64Lte2False   = 6.;
    uint64Lte2Wrapper->set_value(uint64Lte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt64Lte2False" << endl;
    
    // UInt64 Gt
    test1::UInt64Gt uint64Gt;  
    UInt64Value* uint64GtWrapper = uint64Gt.mutable_val();  
    uint64_t uint64GtTrue    = 6.;
    uint64GtWrapper->set_value(uint64GtTrue);  
    if (testMessage(uint64Gt, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt64GtTrue" << endl;
    
    uint64_t uint64GtFalse   = 4.;
    uint64GtWrapper->set_value(uint64GtFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt64GtFalse" << endl;
    
    // UInt64 Gte
    test1::UInt64Gte uint64Gte;  
    UInt64Value* uint64GteWrapper = uint64Gte.mutable_val();  
    uint64_t uint64GteTrue    = 5.;
    uint64GteWrapper->set_value(uint64GteTrue);  
    if (testMessage(uint64Gte, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt64GteTrue" << endl;
    
    uint64_t uint64GteFalse   = 4.;
    uint64GteWrapper->set_value(uint64GteFalse);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt64GteFalse" << endl;
    
    // UInt64 Gte2
    test1::UInt64Gte2 uint64Gte2;  
    UInt64Value* uint64Gte2Wrapper = uint64Gte2.mutable_val();  
    uint64_t uint64Gte2True    = 6.;
    uint64Gte2Wrapper->set_value(uint64Gte2True);  
    if (testMessage(uint64Gte2, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: UInt64Gte2True" << endl;
    
    uint64_t uint64Gte2False   = 4.;
    uint64Gte2Wrapper->set_value(uint64Gte2False);  
    if (testMessage(doubleGt, Validator::ValidationOutput::NOT_VALIDATED))
        testsPassed++;
    else 
        cout << "FAILED: UInt64Gte2False" << endl;
    
    
    cout << "PASSED "  << testsPassed << " tests out of 70" << endl;
    
    if (testsPassed == 70)
        return true;
    else return false;
    
}



bool test2_failures () {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int testsPassed = 0;
    
    // testing wrong types
    test2::WrongTypes wrongTypes;
    
    Int64Value* int64val1Wrapper = wrongTypes.mutable_val1();  
    int64_t val1    = 5.;
    int64val1Wrapper->set_value(val1);
    
    Int64Value* int64val2Wrapper = wrongTypes.mutable_val2();  
    int64_t val2    = 4.;
    int64val2Wrapper->set_value(val2);  
    
    Int64Value* int64val3Wrapper = wrongTypes.mutable_val3();  
    int64_t val3    = 5.;
    int64val3Wrapper->set_value(val3);  
    
    Int64Value* int64val4Wrapper = wrongTypes.mutable_val4();  
    int64_t val4    = 4.;
    int64val4Wrapper->set_value(val4);  
    
    Int64Value* int64val5Wrapper = wrongTypes.mutable_val5();  
    int64_t val5    = 6.;
    int64val5Wrapper->set_value(val5);  
    
    Int64Value* int64val6Wrapper = wrongTypes.mutable_val6();  
    int64_t val6    = 5.;
    int64val6Wrapper->set_value(val6);  
    
    Int64Value* int64val7Wrapper = wrongTypes.mutable_val7();  
    int64_t val7    = 6.;
    int64val7Wrapper->set_value(val7);  
    
    if (testMessage(wrongTypes, Validator::ValidationOutput::INPUT_ERRORS)) 
        testsPassed++;
    else 
        cout << "FAILED: WrongTypes" << endl;
    
    
    
    // testing no options
    
    test2::NoOptions noOptions;
    
    Int64Value* int64val8Wrapper = noOptions.mutable_val8();  
    int64_t val8     = 5.;
    int64val8Wrapper->set_value(val8);
    
    Int64Value* int64val9Wrapper = noOptions.mutable_val9();  
    int64_t val9     = 4.;
    int64val9Wrapper->set_value(val9);  
    
    Int64Value* int64val10Wrapper = noOptions.mutable_val10();  
    int64_t val10    = 5.;
    int64val10Wrapper->set_value(val10);  
    
    Int64Value* int64val11Wrapper = noOptions.mutable_val11();  
    int64_t val11    = 4.;
    int64val11Wrapper->set_value(val11);  
    
    Int64Value* int64val12Wrapper = noOptions.mutable_val12();  
    int64_t val12    = 6.;
    int64val12Wrapper->set_value(val12);  
    
    Int64Value* int64val13Wrapper = noOptions.mutable_val13();  
    int64_t val13    = 5.;
    int64val13Wrapper->set_value(val13);  
    
    Int64Value* int64val14Wrapper = noOptions.mutable_val14();  
    int64_t val14    = 6.;
    int64val14Wrapper->set_value(val14);  
    
    if (testMessage(noOptions, Validator::ValidationOutput::NOTHING_TO_CHECK)) 
        testsPassed++;
    else 
        cout << "FAILED: NoOptions" << endl;
    
    
    // testing multiple options
    
    test2::MultipleOptions1 multipleOptions1;
    
    DoubleValue* doubleval15Wrapper = multipleOptions1.mutable_val15();  
    double val15    = 5.;
    doubleval15Wrapper->set_value(val15);  
    
    if (testMessage(multipleOptions1, Validator::ValidationOutput::VALIDATED)) 
        testsPassed++;
    else 
        cout << "FAILED: MultipleOptions1" << endl;
    
    
    test2::MultipleOptions2 multipleOptions2;
    
    DoubleValue* doubleval16Wrapper = multipleOptions2.mutable_val16();  
    double val16    = 5.;
    doubleval16Wrapper->set_value(val16);  
    
    if (testMessage(multipleOptions2, Validator::ValidationOutput::INPUT_ERRORS)) 
        testsPassed++;
    else 
        cout << "FAILED: MultipleOptions2" << endl;
    
    
    test2::MultipleOptions3 multipleOptions3;
    
    DoubleValue* doubleval17Wrapper = multipleOptions3.mutable_val17();  
    double val17    = 5.;
    doubleval17Wrapper->set_value(val17);  
    
    if (testMessage(multipleOptions3, Validator::ValidationOutput::INPUT_ERRORS)) 
        testsPassed++;
    else 
        cout << "FAILED: MultipleOptions3" << endl;
    
    
    cout << "PASSED "  << testsPassed << " tests out of 5" << endl;
    
    if (testsPassed == 5)
        return true;
    else return false;
}



