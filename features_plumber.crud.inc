<?php
// $Id$

/**
 * @file
 * CRUD functions for Features Plumber.
 */

ctools_include('export');

/**
 * Load all records.
 */
function features_plumber_records_load_all($reset = FALSE) {
  return ctools_export_crud_load_all('features_plumber', $reset);
}

/**
 * Load all records by feature name.
 */
function features_plumber_records_load_by_feature($feature) {
  return ctools_export_load_object('features_plumber', 'conditions', array('feature' => $feature));
}