def options(opt):
  opt.load('compiler_cxx')

def configure(conf):
  conf.load('compiler_cxx')
  #conf.check(header_name='jni.h', features='cxx')
  conf.env.INCLUDES_JNI = ['/usr/lib/jvm/default-java/include',
                           '/usr/lib/jvm/default-java/include/linux']

def build(bld):
  bld.program(source=['src/Dense_call.cpp'], 
              target='dense', 
              use='JNI',
              cxxflags  = '-g -std=c++11 -fdiagnostics-color=always -Wall')
  #bld.program(source=[#'src/Tree_call.cpp', 
  #                    #'src/ClustData.cpp',
  #                    #'src/mfaTree.cpp', 
  #                    #'src/Utility.cpp',
  #                    'src/Vertex.cpp',
  #                    #'src/Ord_Set.cpp',
  #                    #'src/Graph.cpp',
  #                    #'src/GraphUpdate.cpp',
  #                    'src/Cluster.cpp',
  #                    'src/Edge.cpp',
  #                    'src/DegValues.cpp',
  #                    #'src/Node.cpp',
  #                    #'src/StringFunction.cpp',
  #                    #'src/Condition.cpp',
  #                    #'src/Solver.cpp',
  #                    #'src/Distribution.cpp',
  #                    #'src/GetCluster.cpp',
  #                    #'src/DRTree.cpp',
  #                    #'src/Print.cpp',
  #                    #'src/Equation.cpp',
  #                    #'src/MFAAlgo.cpp'
  #                   ], 
  #            target='do_it_separate', 
  #            use='JNI',
  #            cxxflags  = '-g -std=c++11 -fdiagnostics-color=always -Wall')
