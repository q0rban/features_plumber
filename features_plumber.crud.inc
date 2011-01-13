<?php
// $Id$

/**
 * @file
 * CRUD functions for Features Plumber.
 */

/**
 * Load all records.
 */
function features_plumber_records_load_all($reset = FALSE) {
  ctools_include('export');
  return ctools_export_crud_load_all('features_plumber', $reset);
}