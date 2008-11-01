package xpl.semantic;

import xpl.semantic.symbols.*;

import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Opcodes;

import java.util.*;

public class SymbolTable implements Opcodes {
  public SymbolTable() {
    enterNewFrame();

    current.put("puts",  new Method(Types.Void,    "puts",  new Type[] { Types.String  }, true));
    current.put("print", new Method(Types.Void,    "print", new Type[] { Types.Integer }, true));
    current.put("power", new Method(Types.Integer, "power", new Type[] { Types.Integer, Types.Integer }, true));
  }

  private ArrayList<Frame> frames = new ArrayList<Frame>();
  public int getCurrentFrameId() { return frames.size()-1; }

  private Frame current = null;

  public Identifier findIdentifier(String name) { return current.find(name, Identifier.class); }
  public Argument   findArgument  (String name) { return current.find(name, Argument.class);   }
  public Variable   findVariable  (String name) { return current.find(name, Variable.class);   }
  public Method     findMethod    (String name) { return current.find(name, Method.class);     }

  public void put(Symbol sym) {
    current.put(sym.getName(), sym);
  }

  public void enterFrame(int id) {
    current = frames.get(id);
  }

  public void enterNewFrame() {
    current = new Frame(current);
    frames.add(current);
  }

  public void exitFrame()  {
    current = current.getParent();
  }

  public String toString() {
    return current.toString();
  }
}