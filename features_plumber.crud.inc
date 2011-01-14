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

/**
 * Write a record.
 */
function features_plumber_record_save(&$record) {
  $update = (isset($record->record_id) && is_numeric($record->record_id)) ? array('record_id') : array();
  if ($return = drupal_write_record('features_plumber', $record, $update)) {
    ctools_export_load_object_reset('features_plumber');
  }
  return $return;
}

/**
 * Generate a name.
 */
function features_plumber_generate_name($feature, $component, $component_val) {
  return implode('__', compact('feature', 'component', 'component_val'));
}