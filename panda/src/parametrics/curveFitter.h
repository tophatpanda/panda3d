// Filename: curveFitter.h
// Created by:  drose (17Sep98)
// 
////////////////////////////////////////////////////////////////////
// Copyright (C) 1992,93,94,95,96,97  Walt Disney Imagineering, Inc.
// 
// These  coded  instructions,  statements,  data   structures   and
// computer  programs contain unpublished proprietary information of
// Walt Disney Imagineering and are protected by  Federal  copyright
// law.  They may  not be  disclosed to third  parties  or copied or
// duplicated in any form, in whole or in part,  without  the  prior
// written consent of Walt Disney Imagineering Inc.
////////////////////////////////////////////////////////////////////

#ifndef CURVEFITTER_H
#define CURVEFITTER_H

#include <pandabase.h>

#include <typedef.h>
////#include <linMathOutput.h>
#include "luse.h"
#include <vector>
////#include <Performer/pr/pfLinMath.h>

class HermiteCurve;
class NurbsCurve;
class ParametricCurve;

////////////////////////////////////////////////////////////////////
//       Class : CurveFitter
// Description : 
////////////////////////////////////////////////////////////////////
class CurveFitter {
PUBLISHED:
  void reset();
  void add_point(double t, const LVector3f &point);

  void sample(ParametricCurve *curve, int count, bool even);
  void generate_even(int count, double net_distance, double net_time);

  void wrap_hpr();
  void compute_timewarp(const ParametricCurve *xyz);
  void sort_points();
  void desample(double factor);

  void compute_tangents(double scale);
  HermiteCurve *make_hermite() const;
  NurbsCurve *make_nurbs() const;
  
  void print() const;

public:
  void output(ostream &out) const;

  class DataPoint {
  public:
    DataPoint() : _t(0.0), _point(0.0, 0.0, 0.0), _tangent(0.0, 0.0, 0.0) { }
    void output(ostream &out) const {
      out << "Time " << _t << " point " << _point << " tan " << _tangent;
    }

    int operator < (const DataPoint &other) const {
      return _t < other._t;
    }
    
    double _t;
    LVector3f _point;
    LVector3f _tangent;
  };
  
  typedef vector<DataPoint> Data;
  Data _data;

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    register_type(_type_handle, "CurveFitter");
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}
 
private:
  static TypeHandle _type_handle;
};

inline ostream &operator << (ostream &out, const CurveFitter::DataPoint &dp) {
  dp.output(out);
  return out;
}

inline ostream &operator << (ostream &out, const CurveFitter &cf) {
  cf.output(out);
  return out;
}

#endif
