/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {
class CallOpInterface;
namespace detail {
struct CallOpInterfaceInterfaceTraits {
  struct Concept {
    ::mlir::CallInterfaceCallable (*getCallableForCallee)(const Concept *impl, ::mlir::Operation *);
    ::mlir::Operation::operand_range (*getArgOperands)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::CallOpInterface;
    Model() : Concept{getCallableForCallee, getArgOperands} {}

    static inline ::mlir::CallInterfaceCallable getCallableForCallee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Operation::operand_range getArgOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::CallOpInterface;
    FallbackModel() : Concept{getCallableForCallee, getArgOperands} {}

    static inline ::mlir::CallInterfaceCallable getCallableForCallee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::Operation::operand_range getArgOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};template <typename ConcreteOp>
struct CallOpInterfaceTrait;

} // namespace detail
class CallOpInterface : public ::mlir::OpInterface<CallOpInterface, detail::CallOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<CallOpInterface, detail::CallOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::CallOpInterfaceTrait<ConcreteOp> {};
  /// Returns the callee of this call-like operation. A `callee` is either a
  /// reference to a symbol, via SymbolRefAttr, or a reference to a defined
  /// SSA value. If the reference is an SSA value, the SSA value corresponds
  /// to a region of a lambda-like operation.
  ::mlir::CallInterfaceCallable getCallableForCallee();
  /// Returns the operands within this call that are used as arguments to the
  /// callee.
  ::mlir::Operation::operand_range getArgOperands();

    /// Resolve the callable operation for given callee to a
    /// CallableOpInterface, or nullptr if a valid callable was not resolved.
    /// `symbolTable` is an optional parameter that will allow for using a
    /// cached symbol table for symbol lookups instead of performing an O(N)
    /// scan.
    Operation *resolveCallable(SymbolTableCollection *symbolTable = nullptr);
  
};
namespace detail {
  template <typename ConcreteOp>
  struct CallOpInterfaceTrait : public ::mlir::OpInterface<CallOpInterface, detail::CallOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };
}// namespace detail
} // namespace mlir
namespace mlir {
class CallableOpInterface;
namespace detail {
struct CallableOpInterfaceInterfaceTraits {
  struct Concept {
    ::mlir::Region *(*getCallableRegion)(const Concept *impl, ::mlir::Operation *);
    ::llvm::ArrayRef<::mlir::Type> (*getCallableResults)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::mlir::CallableOpInterface;
    Model() : Concept{getCallableRegion, getCallableResults} {}

    static inline ::mlir::Region *getCallableRegion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::ArrayRef<::mlir::Type> getCallableResults(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::mlir::CallableOpInterface;
    FallbackModel() : Concept{getCallableRegion, getCallableResults} {}

    static inline ::mlir::Region *getCallableRegion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::llvm::ArrayRef<::mlir::Type> getCallableResults(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};template <typename ConcreteOp>
struct CallableOpInterfaceTrait;

} // namespace detail
class CallableOpInterface : public ::mlir::OpInterface<CallableOpInterface, detail::CallableOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<CallableOpInterface, detail::CallableOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::CallableOpInterfaceTrait<ConcreteOp> {};
  /// Returns the region on the current operation that is callable. This may
  /// return null in the case of an external callable object, e.g. an external
  /// function.
  ::mlir::Region *getCallableRegion();
  /// Returns the results types that the callable region produces when
  /// executed.
  ::llvm::ArrayRef<::mlir::Type> getCallableResults();
};
namespace detail {
  template <typename ConcreteOp>
  struct CallableOpInterfaceTrait : public ::mlir::OpInterface<CallableOpInterface, detail::CallableOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };
}// namespace detail
} // namespace mlir
namespace mlir {
template<typename ConcreteOp>
::mlir::CallInterfaceCallable detail::CallOpInterfaceInterfaceTraits::Model<ConcreteOp>::getCallableForCallee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getCallableForCallee();
}
template<typename ConcreteOp>
::mlir::Operation::operand_range detail::CallOpInterfaceInterfaceTraits::Model<ConcreteOp>::getArgOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getArgOperands();
}
template<typename ConcreteOp>
::mlir::CallInterfaceCallable detail::CallOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getCallableForCallee(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getCallableForCallee(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::Operation::operand_range detail::CallOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getArgOperands(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getArgOperands(tablegen_opaque_val);
}
} // namespace mlir
namespace mlir {
template<typename ConcreteOp>
::mlir::Region *detail::CallableOpInterfaceInterfaceTraits::Model<ConcreteOp>::getCallableRegion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getCallableRegion();
}
template<typename ConcreteOp>
::llvm::ArrayRef<::mlir::Type> detail::CallableOpInterfaceInterfaceTraits::Model<ConcreteOp>::getCallableResults(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getCallableResults();
}
template<typename ConcreteOp>
::mlir::Region *detail::CallableOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getCallableRegion(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getCallableRegion(tablegen_opaque_val);
}
template<typename ConcreteOp>
::llvm::ArrayRef<::mlir::Type> detail::CallableOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getCallableResults(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getCallableResults(tablegen_opaque_val);
}
} // namespace mlir
