// This is a convienience wrapper around the work the ant task does -
// the task compiles the given .xpl program, saves the compilation
// output, runs it, saves the output of the run and finally diff's the
// output of the run with an predefined output. This class uses the
// JUnit interface to see if the output is correct and signal errors
// using the compilation output and the diff.

import java.io.*;
import java.util.*;

import org.junit.*;
import static junit.framework.Assert.*;

import org.apache.commons.io.*;
import org.apache.commons.io.filefilter.*;

public class IntegrationTest {
  private String filename, path, basename;

  @Test
  public void keepsLanguageConformance() {
    File           dir    = new File("tests/integration");
    FilenameFilter filter = new RegexFileFilter("^.*\\.xpl$");
    File[]         files  = dir.listFiles(filter);

    for (File xplProgramFile : files) {
      filename  = xplProgramFile.toString();
      path      = FilenameUtils.getPath(filename);
      basename  = FilenameUtils.getBaseName(filename);

      checkIfWasCompiled(xplProgramFile);
      checkIfOutputWasCorrect(xplProgramFile);
    }
  }

  private void checkIfWasCompiled(File xplProgramFile) {
    File xplClassFile = new File(path + basename + ".class");
    if(!xplClassFile.exists()) {
      String error         =  xplProgramFile + " compilation output isn't available";
      String compileOutput = readFromFile(path + basename + ".compilation", error);
      fail(xplProgramFile + " couldn't be compiled\n" + compileOutput);
    }
  }

  private void checkIfOutputWasCorrect(File xplProgramFile) {
    String error         = xplProgramFile + " outputs aren't available";
    String desiredOutput = readFromFile(path + basename + ".output-desired", error);
    String currentOutput = readFromFile(path + basename + ".output-current", error);

    if(!currentOutput.equals(desiredOutput)) {
      String outputsDiff = readFromFile(path + basename + ".output-diff", error);
      fail(xplProgramFile + " gave incorrect output\n" + outputsDiff);
    }
  }

  private String readFromFile(String filename, String errorMessage) {
    try {
      return listToString(FileUtils.readLines(new File(filename)));
    }
    catch(IOException e) { fail(errorMessage); }

    return null;
  }

  private String listToString(List list) {
    String result = "";
    for(Object o : list)
      result += (o.toString() + "\n");
    return result;
  }
}
