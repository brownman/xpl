import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.MethodVisitor;

public class CodeGeneratorMisc extends CodeGeneratorModule {
  public CodeGeneratorMisc(Context context) { super(context); }

  private int stackDepth = 0;
  public int getStackDepth() { return stackDepth; }

  public void load(int number) { stackDepth += 1; currentMethod.visitLdcInsn(number); }

  public void pushThis() {
    currentMethod.visitVarInsn(ALOAD, 0);
  };

  public void storeVariable(String name) {
    LocalVariable var = scope.findLocalVariable(name);
    if(!var.isInitialized()) {
      classWriter.visitField(ACC_PUBLIC, var.getVariableId(), "I", "", null);
      var.makeInitialized();
    }
    currentMethod.visitFieldInsn(PUTFIELD, className, var.getVariableId(), "I");
  }

  public void loadVariable(String name) {
    Variable var = scope.findVariable(name);

    if(var.isOfType("argument")) {
      Argument arg = (Argument) var;
      currentMethod.visitVarInsn(ILOAD, arg.getId());
    }
    else if (var.isOfType("local-variable")) {
      LocalVariable lVar = (LocalVariable) var;
      currentMethod.visitVarInsn(ALOAD, 0);
      currentMethod.visitFieldInsn(GETFIELD, className, lVar.getVariableId(), "I");
    }
  }

  public void finish() {
    currentMethod.visitInsn(RETURN);
    currentMethod.visitMaxs(stackDepth, 1);
    currentMethod.visitEnd();
  }
}
